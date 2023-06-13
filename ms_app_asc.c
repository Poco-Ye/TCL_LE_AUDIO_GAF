
__STATIC uint16_t app_asc_att_read_get(uint16_t att_idx, co_buf_t** pp_buf)
{
    uint16_t status = GAP_ERR_NO_ERROR;
    //const void* p_tx = NULL;
    int32_t cb_tx = 0;



    switch (att_idx)
    {
        case ASCS_ASE_SINK1_VAL:
            {
                dbg_print("read ASCS_ASE_SINK1_VAL\r\n");
                struct asc_chr_ase ase_snk;
                ase_snk.ase_id = SINK1;
                ase_snk.ase_state = BT_AUDIO_EP_STATE_IDLE;
                cb_tx = sizeof(ase_snk) ;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), &ase_snk, cb_tx);
                }

                return status;
            }

        case ASCS_ASE_SINK1_CFG:
            {
                uint8_t localValue[] = "ASCS_ASE_SINK1_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }
        case ASCS_ASE_SINK2_VAL:
            {
                dbg_print("read ASCS_ASE_SINK2_VAL\r\n");
                struct asc_chr_ase ase_snk;
                ase_snk.ase_id = SINK2;
                ase_snk.ase_state = BT_AUDIO_EP_STATE_IDLE;
                cb_tx = sizeof(ase_snk) ;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), &ase_snk, cb_tx);
                }

                return status;
            }

        case ASCS_ASE_SINK2_CFG:
            {
                uint8_t localValue[] = "ASCS_ASE_SINK2_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }

        case ASCS_ASE_SRC1_VAL:
            {
                dbg_print("read ASCS_ASE_SRC1_VAL\r\n");
                struct asc_chr_ase ase_src;
                ase_src.ase_id = SRC1;
                ase_src.ase_state = BT_AUDIO_EP_STATE_IDLE;
                cb_tx = sizeof(ase_src) ;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), &ase_src, cb_tx);
                }
                return status;
            }
        case  ASCS_ASE_SRC1_CFG:
            {
                uint8_t localValue[] = "ASCS_ASE_SRC1_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }
        case ASCS_ASE_SRC2_VAL:
            {
                dbg_print("read ASCS_ASE_SRC2_VAL\r\n");
                struct asc_chr_ase ase_src;
                ase_src.ase_id = SRC2;
                ase_src.ase_state = BT_AUDIO_EP_STATE_IDLE;
                cb_tx = sizeof(ase_src) ;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), &ase_src, cb_tx);
                }
                return status;
            }
        case  ASCS_ASE_SRC2_CFG:
            {
                uint8_t localValue[] = "ASCS_ASE_SRC2_CFG";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		
                return status;
            }

        case ASCS_ASE_CP_VAL:
            {
                dbg_print("read ASCS_ASE_CP_VAL\r\n");
                uint8_t localValue[] = "ASCS_ASE_CP_VAL";
                cb_tx = sizeof(localValue) - 1;
                status = co_buf_alloc(pp_buf, GATT_BUFFER_HEADER_LEN, cb_tx, GATT_BUFFER_TAIL_LEN);

                if (status == CO_BUF_ERR_NO_ERROR)
                {
                    memmove(co_buf_data(*pp_buf), localValue, cb_tx);
                }		

                return status;
            }
        case  ASCS_ASE_CP_CFG:
            {
                uint8_t localValue[] = "ASCS_ASE_CP_CFG";
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


__STATIC uint16_t app_asc_att_set(uint8_t conidx,uint16_t att_idx, co_buf_t* p_buf)
{
    uint16_t status = GAP_ERR_NO_ERROR;
    uint8_t* value = co_buf_data(p_buf);
    uint16_t length = co_buf_data_len(p_buf);

    dbg_print("app_asc_att_set %d,length:%d\r\n", att_idx,length);

    switch (att_idx)
    {

        case ASCS_ASE_SINK1_VAL:
            {

                dbg_print("ASCS_ASE_SINK1_VAL\r\n");

                status = GAP_ERR_NO_ERROR;
                break;
            }
        case ASCS_ASE_SINK1_CFG:
            {        
                uint16_t ntf_cfg = value[0];
                dbg_print("ASC SINK1 NTF Started\r\n");
                if(ntf_cfg == ASC_PRF_CLI_START_NTF)
                {
                    gAscSINKNtf1 = true;
                    g_asc_state = true;

                }
                else if(ntf_cfg == ASC_PRF_CLI_STOP_NTFIND)
                {
                    gAscSINKNtf1 = false;
                    dbg_print("ASC SINK1 NTF Stoped\r\n");
                }
                status = GAP_ERR_NO_ERROR;
                break;
            }
        case ASCS_ASE_SINK2_VAL:
            {
                dbg_print("ASCS_ASE_SINK2_VAL\r\n");

                status = GAP_ERR_NO_ERROR;
                break;
            }
        case ASCS_ASE_SINK2_CFG:
            {        
                uint16_t ntf_cfg = value[0];
                dbg_print("ASC SINK2 NTF Started\r\n");
                if(ntf_cfg == ASC_PRF_CLI_START_NTF)
                {
                    gAscSINKNtf2 = true;
                    g_asc_state = true;

                }
                else if(ntf_cfg == ASC_PRF_CLI_STOP_NTFIND)
                {
                    gAscSINKNtf2 = false;
                    dbg_print("ASC SINK2 NTF Stoped\r\n");
                }
                status = GAP_ERR_NO_ERROR;
                break;
            }

        case ASCS_ASE_SRC1_VAL:
            {

                dbg_print("ASCS_ASE_SRC1_VAL\r\n");

                status = GAP_ERR_NO_ERROR;
                break;
            }
        case ASCS_ASE_SRC1_CFG:
            {

                uint16_t ntf_cfg = value[0];
                if(ntf_cfg == ASC_PRF_CLI_START_NTF)
                {
                    gAscSRCNtf1 = true;
                    dbg_print("ASC SRC NTF Started\r\n");

                }
                else if(ntf_cfg == ASC_PRF_CLI_STOP_NTFIND)
                {
                    gAscSRCNtf1 = false;
                    dbg_print("ASC SRC NTF Stopped\r\n");
                }
                status = GAP_ERR_NO_ERROR;
                break;

            }
        case ASCS_ASE_SRC2_VAL:
            {

                dbg_print("ASCS_ASE_SRC2_VAL\r\n");

                status = GAP_ERR_NO_ERROR;
                break;
            }
        case ASCS_ASE_SRC2_CFG:
            {

                uint16_t ntf_cfg = value[0];
                if(ntf_cfg == ASC_PRF_CLI_START_NTF)
                {
                    gAscSRCNtf2 = true;
                    dbg_print("ASC SRC NTF Started\r\n");

                }
                else if(ntf_cfg == ASC_PRF_CLI_STOP_NTFIND)
                {
                    gAscSRCNtf2 = false;
                    dbg_print("ASC SRC NTF Stopped\r\n");
                }
                status = GAP_ERR_NO_ERROR;
                break;

            }

        case ASCS_ASE_CP_VAL:
            {
                dbg_print("ASCS_ASE_CP_VAL\r\n");
                struct bt_ascs_ase_cp *req_cp = (struct  bt_ascs_ase_cp *)value;

                switch(req_cp->op)
                {
                    case BT_ASCS_CONFIG_OP:
                        {
                            struct bt_ascs_config_op *req = (struct bt_ascs_config_op  *)req_cp->pdu;

                            struct bt_ascs_config * cfg =  req->cfg;
                            uint8_t spec_len,*spec,*sp;


                            uint8_t cp_rsp_len = sizeof(struct bt_ascs_cp_rsp);
                            uint8_t ase_rsp_len = sizeof(struct bt_ascs_cp_ase_rsp);
                            uint8_t rsp_data_len = cp_rsp_len + req->num_ases * ase_rsp_len;
                            uint8_t rsp_data[rsp_data_len];
                            struct bt_ascs_cp_rsp *rsp = (struct bt_ascs_cp_rsp*)rsp_data;
                            rsp->op = req_cp->op;
                            rsp->num_ase = req->num_ases;

                            uint8_t config_rsp_data_len = sizeof(struct bt_ascs_ase_status_config_rsp)+sizeof(struct bt_ascs_ase_status_config) + cfg->cc_len;
                            uint8_t config_rsp_data[config_rsp_data_len];
                            struct bt_ascs_ase_status_config_rsp *config_rsp = (struct bt_ascs_ase_status_config_rsp *)config_rsp_data;

                            config_rsp->ase_state = BT_CODEC_CONFIGURED;
                            config_rsp->status_config->framing = false;
                            config_rsp->status_config->phy = BT_GAP_LE_PHY_1M;
                            config_rsp->status_config->rtn = 0x3;
                            config_rsp->status_config->latency = 10;
                            uint32_t min = 3000;
                            memmove(config_rsp->status_config->pd_min, &min, 3);
                            uint32_t max = 3000;
                            memmove(config_rsp->status_config->pd_max, &max, 3);
                            min = 0;
                            memmove(config_rsp->status_config->prefer_pd_min, &min, 3);
                            max = 0;
                            memmove(config_rsp->status_config->prefer_pd_max, &max, 3);


                            for(uint8_t i=0;i<req->num_ases;i++)
                            {
                                config_rsp->ase_id = cfg->ase;
                                memmove(&config_rsp->status_config->codec, &cfg->codec, sizeof(struct bt_ascs_codec));
                                memmove(&config_rsp->status_config->cc_len, &cfg->cc_len, sizeof(cfg->cc_len)+cfg->cc_len);
                                switch(cfg->ase)
                                {
                                    case SINK1:
                                        dbg_print("send sink1 config ntf\r\n");
                                        ascs_send_data_via_sink1_ntf(config_rsp_data_len,config_rsp_data);
                                        break;
                                    case SINK2:
                                        dbg_print("send sink2 config ntf\r\n");
                                        ascs_send_data_via_sink2_ntf(config_rsp_data_len,config_rsp_data);
                                        break;
                                    case SRC1:
                                        dbg_print("send src1 config ntf\r\n");
                                        ascs_send_data_via_src1_ntf(config_rsp_data_len,config_rsp_data);
                                        break;
                                    case SRC2:
                                        dbg_print("send src2 config ntf\r\n");
                                        ascs_send_data_via_src2_ntf(config_rsp_data_len,config_rsp_data);
                                        break;
                                    default:
                                        break;
                                }


                                rsp->ase_rsp[i].id = cfg->ase;
                                rsp->ase_rsp[i].code = BT_ASCS_RSP_SUCCESS;
                                rsp->ase_rsp[i].reason = BT_ASCS_REASON_NONE;


                                spec_len = cfg->cc_len;
                                spec = (uint8_t*)cfg->cc;
                                sp = spec;
                                uint8_t id = cfg->ase - 1;
                                while(sp-spec<spec_len)
                                {
                                    struct  bt_ascs_codec_config *data = (struct bt_ascs_codec_config*)sp;
                                    switch(data->type)
                                    {
                                        case BT_CODEC_CONFIG_LC3_FREQ:
                                            {
#if (BLE_ISO_PCM)
                                                g_param[id].bit_depth = 16;
#endif
                                                uint8_t *frequency = data->data;
                                                switch(*frequency)
                                                {
                                                    case BT_CODEC_CONFIG_LC3_FREQ_8KHZ:
#if (BLE_ISO_PCM)
                                                        g_param[id].sample_rate = 8000;
#endif
                                                        break;
                                                    case BT_CODEC_CONFIG_LC3_FREQ_16KHZ:
#if (BLE_ISO_PCM)
                                                        g_param[id].sample_rate = 16000;
#endif
                                                        break;
                                                    case BT_CODEC_CONFIG_LC3_FREQ_24KHZ:
#if (BLE_ISO_PCM)
                                                        g_param[id].sample_rate = 24000;
#endif
                                                        break;
                                                    case BT_CODEC_CONFIG_LC3_FREQ_32KHZ:
#if (BLE_ISO_PCM)
                                                        g_param[id].sample_rate = 32000;
#endif
                                                        break;
                                                    case BT_CODEC_CONFIG_LC3_FREQ_44KHZ:
#if (BLE_ISO_PCM)
                                                        g_param[id].sample_rate = 44000;
#endif
                                                        break;
                                                    case BT_CODEC_CONFIG_LC3_FREQ_48KHZ:
#if (BLE_ISO_PCM)
                                                        g_param[id].sample_rate = 48000;
#endif
                                                        break;
                                                    default:
                                                        break;
                                                }
                                            }
                                            break;
                                        case BT_CODEC_CONFIG_LC3_DURATION:
                                            {
                                                uint8_t *duration = data->data;
                                                switch(*duration)
                                                {
                                                    case BT_CODEC_CONFIG_LC3_DURATION_7_5:
#if (BLE_ISO_PCM)
                                                        g_param[id].frame_duration = 7500;
#endif
                                                        break;
                                                    case BT_CODEC_CONFIG_LC3_DURATION_10:
#if (BLE_ISO_PCM)
                                                        g_param[id].frame_duration = 10000;
#endif
                                                        break;
                                                    default:
                                                        break;
                                                }
                                            }
                                            break;
                                        case BT_CODEC_CONFIG_LC3_CHAN_ALLOC:
                                            {

                                            }
                                            break;
                                        case BT_CODEC_CONFIG_LC3_FRAME_LEN:
                                            {
#if (BLE_ISO_PCM)
                                                uint16_t *bytes = (uint16_t *)data->data;   
                                                g_param[id].nbytes = *bytes;
                                                g_param[id].nchannels = 1;
#endif
                                            }
                                            break;
                                        default:
                                            break;
                                    }
                                    sp += data->len+sizeof(data->len);
                                }
                                cfg = (struct bt_ascs_config *)sp;

                            }

                            dbg_print("send cp config ntf\r\n");
                            ascs_send_data_via_cp_ntf(rsp_data_len,rsp_data);

                        }
                        break;
                    case BT_ASCS_QOS_OP:
                        {
                            struct bt_ascs_qos_op *req = (struct bt_ascs_qos_op *)req_cp->pdu;

                            //send ntf acp qos rsp
                            uint8_t rsp_data_len = sizeof(struct bt_ascs_cp_rsp) + req->num_ases*sizeof(struct bt_ascs_cp_ase_rsp);
                            uint8_t rsp_data[rsp_data_len];
                            struct bt_ascs_cp_rsp *rsp = (struct bt_ascs_cp_rsp*)rsp_data;
                            rsp->op = req_cp->op;
                            rsp->num_ase = req->num_ases;
                            for(uint8_t i=0;i<req->num_ases;i++)
                            {
                                rsp->ase_rsp[i].id = req->qos[i].ase;
                                rsp->ase_rsp[i].code = BT_ASCS_RSP_SUCCESS;
                                rsp->ase_rsp[i].reason = BT_ASCS_REASON_NONE;
                            }
                            dbg_print("send cp qos ntf\r\n");
                            ascs_send_data_via_cp_ntf(rsp_data_len,rsp_data);

                            //send ntf sink/source qos status
                            uint8_t qos_rsp_data_len = sizeof(struct bt_ascs_ase_status_qos_rsp)+sizeof(struct bt_ascs_ase_status_qos) ;
                            uint8_t qos_rsp_data[qos_rsp_data_len];
                            struct bt_ascs_ase_status_qos_rsp *qos_rsp = (struct bt_ascs_ase_status_qos_rsp *)qos_rsp_data;
                            for(uint8_t i =0;i<req->num_ases;i++)
                            {
                                qos_rsp->ase_id = req->qos[i].ase;
                                qos_rsp->ase_state = BT_QOS_CONFIGURED;

                                memmove(&qos_rsp->status_qos,&req->qos[i].cig,sizeof(struct bt_ascs_ase_status_qos));
                                uint8_t id = qos_rsp->ase_id -1;
                                memmove(&Qos_Req[id],&req->qos[i],sizeof(struct bt_ascs_qos));
#if (BLE_ISO_PCM)
                                g_param[id].prest_delay = req->qos[i].pd[2]<<16|req->qos[i].pd[1]<<8|req->qos[i].pd[0];
#endif
                                switch(qos_rsp->ase_id)
                                {
                                    case SINK1:
                                        dbg_print("send sink1 qos ntf\r\n");
                                        ascs_send_data_via_sink1_ntf(qos_rsp_data_len,qos_rsp_data);
                                        break;
                                    case SINK2:
                                        dbg_print("send sink2 qos ntf\r\n");
                                        ascs_send_data_via_sink2_ntf(qos_rsp_data_len,qos_rsp_data);
                                        break;
                                    case SRC1:
                                        dbg_print("send src1 qos ntf\r\n");
                                        ascs_send_data_via_src1_ntf(qos_rsp_data_len,qos_rsp_data);
                                        break;
                                    case SRC2:
                                        dbg_print("send src2 qos ntf\r\n");
                                        ascs_send_data_via_src2_ntf(qos_rsp_data_len,qos_rsp_data);
                                        break;
                                    default:
                                        break;
                                }
                            }

                        }
                        break;
                    case BT_ASCS_ENABLE_OP:
                        {
                            struct bt_ascs_enable_op *req = (struct bt_ascs_enable_op *)req_cp->pdu;
                            uint8_t rsp_data_len = sizeof(struct bt_ascs_cp_rsp) + req->num_ases*sizeof(struct bt_ascs_cp_ase_rsp);
                            uint8_t rsp_data[rsp_data_len];
                            struct bt_ascs_cp_rsp *rsp = (struct bt_ascs_cp_rsp*)rsp_data;
                            rsp->op = req_cp->op;
                            rsp->num_ase = req->num_ases;



                            uint8_t enable_rsp_data_len = sizeof(struct bt_ascs_ase_status_enable_rsp) + sizeof(struct bt_ascs_ase_status_enable);
                            uint8_t  enable_rsp_data[enable_rsp_data_len];
                            struct bt_ascs_ase_status_enable_rsp *enable_rsp = (struct bt_ascs_ase_status_enable_rsp *)enable_rsp_data;

                            uint8_t stream_rsp_data_len = sizeof(struct bt_ascs_ase_status_stream_rsp) + sizeof(struct bt_ascs_ase_status_stream);
                            uint8_t  stream_rsp_data[stream_rsp_data_len];
                            struct bt_ascs_ase_status_stream_rsp *stream_rsp = (struct bt_ascs_ase_status_stream_rsp *)stream_rsp_data;

                            enable_rsp->ase_state = BT_ENABLING;
                            stream_rsp->ase_state = BT_STREAMING;
                            enable_rsp->status_enable->metadata_len = 0;
                            stream_rsp->status_stream->metadata_len = 0;

                            uint8_t *sp = (uint8_t *)req->metadata;
#if (BLE_ISO_PCM)
                            struct audio_output_param *p_msg = KE_MSG_ALLOC(APP_DATA_PATH_IND, TASK_PCM, TASK_NONE, audio_output_param);
#endif
                            for(uint8_t i=0;i<req->num_ases;i++)
                            {
                                struct bt_ascs_metadata *data = (struct bt_ascs_metadata*)sp;

                                rsp->ase_rsp[i].id = data->ase;
                                rsp->ase_rsp[i].code = BT_ASCS_RSP_SUCCESS;
                                rsp->ase_rsp[i].reason = BT_ASCS_REASON_NONE;

                                stream_rsp->ase_id = enable_rsp->ase_id = data->ase;

                                uint8_t id = data->ase -1;

#if (BLE_ISO_PCM)
                                p_msg->bit_depth = g_param[id].bit_depth;
                                p_msg->sample_rate = g_param[id].sample_rate;
                                p_msg->frame_duration = g_param[id].frame_duration;
                                p_msg->nbytes = g_param[id].nbytes;
                                p_msg->nchannels = g_param[id].nchannels;
                                p_msg->prest_delay = g_param[id].prest_delay;
                                ke_msg_send(p_msg);
#endif
                                enable_rsp->status_enable->cig_id = Qos_Req[id].cig;
                                enable_rsp->status_enable->cis_id = Qos_Req[id].cis;
                                stream_rsp->status_stream->cig_id = Qos_Req[id].cig;
                                stream_rsp->status_stream->cis_id = Qos_Req[id].cis;

                                switch(data->ase)
                                {
                                    case SINK1:
                                        dbg_print("send sink1 enable ntf\r\n");
                                        ascs_send_data_via_sink1_ntf(enable_rsp_data_len,enable_rsp_data);
                                        dbg_print("send sink1 stream ntf\r\n");
                                        ascs_send_data_via_sink1_ntf(stream_rsp_data_len,stream_rsp_data);
                                        break;
                                    case SINK2:
                                        dbg_print("send sink2 enable ntf\r\n");
                                        ascs_send_data_via_sink2_ntf(enable_rsp_data_len,enable_rsp_data);
                                        dbg_print("send sink2 stream ntf\r\n");
                                        ascs_send_data_via_sink2_ntf(stream_rsp_data_len,stream_rsp_data);
                                        break;
                                    case SRC1:
                                        dbg_print("send src1 enable ntf\r\n");
                                        ascs_send_data_via_src1_ntf(enable_rsp_data_len,enable_rsp_data);
                                        dbg_print("send src1 stream ntf\r\n");
                                        ascs_send_data_via_src1_ntf(stream_rsp_data_len,stream_rsp_data);
                                        break;
                                    case SRC2:
                                        dbg_print("send src2 enable ntf\r\n");
                                        ascs_send_data_via_src2_ntf(enable_rsp_data_len,enable_rsp_data);
                                        dbg_print("send src2 stream ntf\r\n");
                                        ascs_send_data_via_src2_ntf(stream_rsp_data_len,stream_rsp_data);
                                        break;
                                    default:
                                        break;
                                }

                                sp += data->len+sizeof(struct bt_ascs_metadata);
                            }

                            dbg_print("send cp enable ntf\r\n");
                            ascs_send_data_via_cp_ntf(rsp_data_len,rsp_data);

                        }
                        break;
                    case BT_ASCS_DISABLE_OP:
                        {
                            struct bt_ascs_disable_op *req = (struct bt_ascs_disable_op *)req_cp->pdu;
                            uint8_t rsp_data_len = sizeof(struct bt_ascs_cp_rsp) + req->num_ases*sizeof(struct bt_ascs_cp_ase_rsp);
                            uint8_t rsp_data[rsp_data_len];
                            struct bt_ascs_cp_rsp *rsp = (struct bt_ascs_cp_rsp*)rsp_data;
                            rsp->op = req_cp->op;
                            rsp->num_ase = req->num_ases;


                            //send ntf sink/source qos status
                            uint8_t qos_rsp_data_len = sizeof(struct bt_ascs_ase_status_qos_rsp)+sizeof(struct bt_ascs_ase_status_qos) ;
                            uint8_t qos_rsp_data[qos_rsp_data_len];
                            struct bt_ascs_ase_status_qos_rsp *qos_rsp = (struct bt_ascs_ase_status_qos_rsp *)qos_rsp_data;


                            for(uint8_t i=0;i<req->num_ases;i++)
                            {

                                qos_rsp->ase_id = req->ase[i];
                                qos_rsp->ase_state = BT_QOS_CONFIGURED;

                                uint8_t id = qos_rsp->ase_id -1 ;
                                memmove(&qos_rsp->status_qos,&Qos_Req[id].cig,sizeof(struct bt_ascs_ase_status_qos));

                                rsp->ase_rsp[i].id = req->ase[i];
                                rsp->ase_rsp[i].code = BT_ASCS_RSP_SUCCESS;
                                rsp->ase_rsp[i].reason = BT_ASCS_REASON_NONE;

                                switch(req->ase[i])
                                {
                                    case SINK1:
                                        dbg_print("send sink1 qos ntf\r\n");
                                        ascs_send_data_via_sink1_ntf(qos_rsp_data_len,qos_rsp_data);
                                        break;
                                    case SINK2:
                                        dbg_print("send sink2 qos ntf\r\n");
                                        ascs_send_data_via_sink2_ntf(qos_rsp_data_len,qos_rsp_data);
                                        break;
                                    case SRC1:
                                        dbg_print("send src1 qos ntf\r\n");
                                        ascs_send_data_via_src1_ntf(qos_rsp_data_len,qos_rsp_data);
                                        break;
                                    case SRC2:
                                        dbg_print("send src2 qos ntf\r\n");
                                        ascs_send_data_via_src2_ntf(qos_rsp_data_len,qos_rsp_data);
                                        break;
                                    default:
                                        break;
                                }

                            }

                            dbg_print("send cp disable ntf\r\n");
                            ascs_send_data_via_cp_ntf(rsp_data_len,rsp_data);

                        }
                        break;
                    default:
                        break;

                }

                status = GAP_ERR_NO_ERROR;
                break;
            }
        case ASCS_ASE_CP_CFG:
            {

                uint16_t ntf_cfg = value[0];
                if(ntf_cfg == ASC_PRF_CLI_START_NTF)
                {
                    gAscCPNtf = true;
                    dbg_print("ASC CP NTF Started\r\n");

                }
                else if(ntf_cfg == ASC_PRF_CLI_STOP_NTFIND)
                {
                    gAscCPNtf = false;
                    dbg_print("ASC CP NTF Stopped\r\n");
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
