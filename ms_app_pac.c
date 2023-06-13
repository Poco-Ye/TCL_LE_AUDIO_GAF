
void pacs_lc3_codec(co_buf_t** pp_buf)
{
    uint8_t buf_f[255];
    uint8_t *buf = buf_f;
    uint8_t copy_len;

    struct  bt_codec lc3_codec={0};

    lc3_codec.num_pac = 1;
    lc3_codec.id = BT_CODEC_LC3_ID;
    lc3_codec.cid = 0x0000;
    lc3_codec.vid = 0x0000;

    copy_len = &lc3_codec.data_count - (uint8_t*)(&lc3_codec);
    memmove(buf,&lc3_codec,copy_len);
    buf+=copy_len;

    uint8_t *buf_data_count = buf;
    buf+=sizeof(lc3_codec.data_count);

    uint16_t freq = BT_CODEC_LC3_FREQ_ANY;
    uint8_t duration = BT_CODEC_LC3_DURATION_ANY;
    uint8_t channel = BT_CODEC_CHANNEL_SUPPORT;
    uint8_t min = 16;
    uint8_t max = 60;
    uint32_t frame = max<<16|min;
    uint8_t max_num = 2;
    for(int i=0;i<CONFIG_BT_CODEC_DATA_COUNT;i++)
    {
        switch(i+1)
        {
            case BT_CODEC_LC3_FREQ:
                lc3_codec.data[i].type = BT_CODEC_LC3_FREQ;
                lc3_codec.data[i].data =(uint8_t*)&freq;
                lc3_codec.data[i].len = sizeof(uint16_t)+ sizeof(lc3_codec.data[i].type);
                break;
            case BT_CODEC_LC3_DURATION:
                lc3_codec.data[i].type = BT_CODEC_LC3_DURATION;
                lc3_codec.data[i].data =&duration;
                lc3_codec.data[i].len = sizeof(uint8_t)+ sizeof(lc3_codec.data[i].type);
                break;
            case BT_CODEC_LC3_CHAN_COUNT:
                lc3_codec.data[i].type = BT_CODEC_LC3_CHAN_COUNT;
                lc3_codec.data[i].data =&channel;
                lc3_codec.data[i].len = sizeof(uint8_t)+ sizeof(lc3_codec.data[i].type);
                break;
            case BT_CODEC_LC3_FRAME_LEN:
                lc3_codec.data[i].type = BT_CODEC_LC3_FRAME_LEN;
                lc3_codec.data[i].data = (uint8_t*)&frame;
                lc3_codec.data[i].len = sizeof(uint32_t)+ sizeof(lc3_codec.data[i].type);
                break;
            case BT_CODEC_LC3_FRAME_COUNT:
                lc3_codec.data[i].type = BT_CODEC_LC3_FRAME_COUNT;
                lc3_codec.data[i].data = &max_num;
                lc3_codec.data[i].len = sizeof(uint8_t)+ sizeof(lc3_codec.data[i].type);
                break;
            default:
                break;
        }

        copy_len = sizeof(lc3_codec.data[i].len);
        memmove(buf,&lc3_codec.data[i].len,copy_len);
        buf+=copy_len;

        copy_len = sizeof(lc3_codec.data[i].type);
        memmove(buf,&lc3_codec.data[i].type,copy_len);
        buf+=copy_len;

        copy_len = lc3_codec.data[i].len - sizeof(lc3_codec.data[i].type);
        memmove(buf,lc3_codec.data[i].data,copy_len);
        buf+=copy_len;


        lc3_codec.data_count += lc3_codec.data[i].len + sizeof(lc3_codec.data[i].len);
    }

    copy_len = sizeof(lc3_codec.data_count);
    memmove(buf_data_count,&lc3_codec.data_count,copy_len);


    uint8_t *buf_meta_count = buf;
    buf+=sizeof(lc3_codec.meta_count);

    uint16_t audio_context = BT_AUDIO_CONTEXT_TYPE_UNSPECIFIED;
    for(int i=0;i<CONFIG_BT_CODEC_METADATA_COUNT;i++)
    {
        switch(i+1)
        {
            case BT_AUDIO_METADATA_TYPE_PREF_CONTEXT:
                lc3_codec.meta[i].type = BT_AUDIO_METADATA_TYPE_PREF_CONTEXT;
                lc3_codec.meta[i].data = (uint8_t*)&audio_context;
                lc3_codec.meta[i].len = sizeof(uint16_t) + sizeof(lc3_codec.meta[i].type);
                break;
            default:
                break;
        }

        copy_len = sizeof(lc3_codec.meta[i].len);
        memmove(buf,&lc3_codec.meta[i].len,copy_len);
        buf+=copy_len;

        copy_len = sizeof(lc3_codec.meta[i].type);
        memmove(buf,&lc3_codec.meta[i].type,copy_len);
        buf+=copy_len;

        copy_len = lc3_codec.meta[i].len - sizeof(lc3_codec.meta[i].type);
        memmove(buf,lc3_codec.meta[i].data,copy_len);
        buf+=copy_len;


        lc3_codec.meta_count += lc3_codec.meta[i].len + sizeof(lc3_codec.meta[i].len);

    }

    copy_len = sizeof(lc3_codec.meta_count);
    memmove(buf_meta_count,&lc3_codec.meta_count,copy_len);

    int32_t cb_tx = buf - buf_f;

    if(cb_tx!=0&&pp_buf!=NULL)
    {
        uint16_t status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);
        if (status == CO_BUF_ERR_NO_ERROR)
        {
            memmove(co_buf_data(*pp_buf), buf_f, cb_tx);
        }		

    }
    else
    {
        dbg_print("pp_buf error\r\n");
    }
}

__STATIC uint16_t app_pac_att_read_get(uint16_t att_idx, co_buf_t** pp_buf)
{
    uint16_t status = GAP_ERR_NO_ERROR;
    //const void* p_tx = NULL;
    int32_t cb_tx = 0;



    switch (att_idx)
    {
        case PACS_PAC_SINK_VAL:
            {
                dbg_print("read PACS_PAC_SINK_VAL\r\n");
                pacs_lc3_codec(pp_buf);

                return status;
            }

        case PACS_PAC_SINK_CFG:
            {
                uint8_t localValue[] = "PACS_PAC_SINK_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }
        case PACS_PAC_LOC_SINK_VAL:
            {
                dbg_print("read PACS_PAC_LOC_SINK_VAL\r\n");
                uint32_t audio_location = BT_CODEC_LOCATION_SUPPORT;
                cb_tx = sizeof(uint32_t) ;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), &audio_location, cb_tx);
                }		

                return status;
            }
        case  PACS_PAC_LOC_SINK_CFG:
            {
                uint8_t localValue[] = "PACS_PAC_LOC_SINK_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }
        case PACS_PAC_SRC_VAL:
            {
                dbg_print("read PACS_PAC_SRC_VAL\r\n");
                pacs_lc3_codec(pp_buf);

                return status;
            }
        case  PACS_PAC_SRC_CFG:
            {
                uint8_t localValue[] = "PACS_PAC_SRC_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }
        case PACS_PAC_LOC_SRC_VAL:
            {
                dbg_print("read PACS_PAC_LOC_SRC_VAL\r\n");
                uint32_t audio_location = BT_CODEC_LOCATION_SUPPORT;
                cb_tx = sizeof(uint32_t) ;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), &audio_location, cb_tx);
                }		

                return status;
            }
        case  PACS_PAC_LOC_SRC_CFG:
            {
                uint8_t localValue[] = "PACS_PAC_LOC_SRC_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }
        case PACS_PAC_AVA_VAL:
            {
                dbg_print("read PACS_PAC_AVA_VAL\r\n");
                uint32_t audio_context_ava = BT_AUDIO_SRC_CONTEXT_AVAILABLE<<16|BT_AUDIO_SNK_CONTEXT_AVAILABLE;
				cb_tx = sizeof(uint32_t) ;
				status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);
				
				if (status == CO_BUF_ERR_NO_ERROR)
				{
				memmove(co_buf_data(*pp_buf), &audio_context_ava, cb_tx);
				}		
                return status;
            }
        case  PACS_PAC_AVA_CFG:
            {
                uint8_t localValue[] = "PACS_PAC_AVA_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }
        case PACS_PAC_SUPP_VAL:
            {
                dbg_print("read PACS_PAC_SUPP_VAL\r\n");
                uint32_t audio_context = BT_AUDIO_SRC_CONTEXT_SUPPORT<<16|BT_AUDIO_SNK_CONTEXT_SUPPORT;
                cb_tx = sizeof(uint32_t) ;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), &audio_context, cb_tx);
                }		

                return status;
            }
        case  PACS_PAC_SUPP_CFG:
            {
                uint8_t localValue[] = "PACS_PAC_SUPP_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }



        default:
            break;
    } // end switch(att_idx)


    return status;
}



__STATIC uint16_t app_pac_att_set(uint8_t conidx,uint16_t att_idx, co_buf_t* p_buf)
{
    uint16_t status = GAP_ERR_NO_ERROR;
    uint8_t* value = co_buf_data(p_buf);
    uint16_t length = co_buf_data_len(p_buf);

    dbg_print("app_pac_att_set %d,length:%x\r\n", att_idx,length);

    switch (att_idx)
    {

        case PACS_PAC_SINK_VAL:

            status = GAP_ERR_NO_ERROR;
            break;
        case PACS_PAC_SINK_CFG:
        {        
			uint16_t ntf_cfg = value[0];
		    dbg_print("PAC SINK NTF Started\r\n");
            if(ntf_cfg == PAC_PRF_CLI_START_NTF)
            {
                gPacSINKNtf = true;
                g_pac_state = true;
                
            }
            else if(ntf_cfg == PAC_PRF_CLI_STOP_NTFIND)
            {
                gPacSINKNtf = false;
		        dbg_print("PAC SINK NTF Stoped\r\n");
            }
            status = GAP_ERR_NO_ERROR;
            break;
        }
        case PACS_PAC_LOC_SINK_VAL:
            
            status = GAP_ERR_NO_ERROR;
            break;
        case PACS_PAC_LOC_SINK_CFG:
        {
                
			uint16_t ntf_cfg = value[0];
            if(ntf_cfg == PAC_PRF_CLI_START_NTF)
            {
                gPacLocSINKNtf = true;
				dbg_print("PAC LOC SINK NTF Started\r\n");
                
            }
            else if(ntf_cfg == PAC_PRF_CLI_STOP_NTFIND)
            {
                gPacLocSINKNtf = false;
				dbg_print("PAC LOC SINK NTF Stopped\r\n");
            }
            status = GAP_ERR_NO_ERROR;
            break;
                    
        }
        case PACS_PAC_SRC_VAL:
            
            status = GAP_ERR_NO_ERROR;
            break;
        case PACS_PAC_SRC_CFG:
        {
                
			uint16_t ntf_cfg = value[0];
            if(ntf_cfg == PAC_PRF_CLI_START_NTF)
            {
                gPacSRCNtf = true;
				dbg_print("PAC SRC NTF Started\r\n");
                
            }
            else if(ntf_cfg == PAC_PRF_CLI_STOP_NTFIND)
            {
                gPacSRCNtf = false;
				dbg_print("PAC SRC NTF Stopped\r\n");
            }
            status = GAP_ERR_NO_ERROR;
            break;
                    
        }
        case PACS_PAC_LOC_SRC_VAL:
            
            status = GAP_ERR_NO_ERROR;
            break;
        case PACS_PAC_LOC_SRC_CFG:
        {
                
			uint16_t ntf_cfg = value[0];
            if(ntf_cfg == PAC_PRF_CLI_START_NTF)
            {
                gPacLocSRCNtf = true;
				dbg_print("PAC LOC SRC NTF Started\r\n");
                
            }
            else if(ntf_cfg == PAC_PRF_CLI_STOP_NTFIND)
            {
                gPacLocSRCNtf = false;
				dbg_print("PAC LOC SRC NTF Stopped\r\n");
            }
            status = GAP_ERR_NO_ERROR;
            break;
                    
        }
        case PACS_PAC_AVA_VAL:
            
            status = GAP_ERR_NO_ERROR;
            break;
        case PACS_PAC_AVA_CFG:
        {
                
			uint16_t ntf_cfg = value[0];
            if(ntf_cfg == PAC_PRF_CLI_START_NTF)
            {
                gPacAVANtf = true;
				dbg_print("PAC AVA NTF Started\r\n");
                
            }
            else if(ntf_cfg == PAC_PRF_CLI_STOP_NTFIND)
            {
                gPacAVANtf = false;
				dbg_print("PAC AVA NTF Stopped\r\n");
            }
            status = GAP_ERR_NO_ERROR;
            break;
                    
        }
        case PACS_PAC_SUPP_VAL:
            
            status = GAP_ERR_NO_ERROR;
            break;
        case PACS_PAC_SUPP_CFG:
        {
                
			uint16_t ntf_cfg = value[0];
            if(ntf_cfg == PAC_PRF_CLI_START_NTF)
            {
                gPacSUPPNtf = true;
				dbg_print("PAC SUPP NTF Started\r\n");
                
            }
            else if(ntf_cfg == PAC_PRF_CLI_STOP_NTFIND)
            {
                gPacSUPPNtf = false;
				dbg_print("PAC SUPP NTF Stopped\r\n");
            }
            status = GAP_ERR_NO_ERROR;
            break;
                    
        }


        default:
            status = ATT_ERR_ATTRIBUTE_NOT_FOUND;
            break;

    } // end switch(att_idx)

    return status;
}

