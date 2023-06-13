/**
 ****************************************************************************************
 *
 * @file app_audio.h
 *
 * @brief  Application AUDIO Module entry point
 *
 *
 * @author yeb
 ****************************************************************************************
 */

#ifndef APP_AUDIO_H_
#define APP_AUDIO_H_


#include "rwip_config.h"     // SW configuration
#include <stdint.h>          // Standard Integer Definition
#include "ke_task.h"         // Kernel Task Definition


struct __PACKED asc_chr_ase
{
    uint8_t ase_id;
    uint8_t ase_state;
};

enum bt_audio_state {
    /** Audio Stream Endpoint Idle state */
    BT_AUDIO_EP_STATE_IDLE =             0x00,
    /** Audio Stream Endpoint Codec Configured state */
    BT_AUDIO_EP_STATE_CODEC_CONFIGURED = 0x01,
    /** Audio Stream Endpoint QoS Configured state */
    BT_AUDIO_EP_STATE_QOS_CONFIGURED =   0x02,
    /** Audio Stream Endpoint Enabling state */
    BT_AUDIO_EP_STATE_ENABLING =         0x03,
    /** Audio Stream Endpoint Streaming state */
    BT_AUDIO_EP_STATE_STREAMING =        0x04,
    /** Audio Stream Endpoint Disabling state */
    BT_AUDIO_EP_STATE_DISABLING =        0x05,
    /** Audio Stream Endpoint Streaming state */
    BT_AUDIO_EP_STATE_RELEASING =        0x06,
};

/**
 *  @brief LC3 codec ID
 */
#define BT_CODEC_LC3_ID                  0x06


#define BIT(ofs)                            (0x1UL << (ofs))

/**
 *  @brief LC3 8 Khz frequency capability
 */
#define BT_CODEC_LC3_FREQ_8KHZ           BIT(0)
/**
 *  @brief LC3 11.025 Khz frequency capability
 */
#define BT_CODEC_LC3_FREQ_11KHZ          BIT(1)
/**
 *  @brief LC3 16 Khz frequency capability
 */
#define BT_CODEC_LC3_FREQ_16KHZ          BIT(2)
/**
 *  @brief LC3 22.05 Khz frequency capability
 */
#define BT_CODEC_LC3_FREQ_22KHZ          BIT(3)
/**
 *  @brief LC3 24 Khz frequency capability
 */
#define BT_CODEC_LC3_FREQ_24KHZ          BIT(4)
/**
 *  @brief LC3 32 Khz frequency capability
 */
#define BT_CODEC_LC3_FREQ_32KHZ          BIT(5)
/**
 *  @brief LC3 44.1 Khz frequency capability
 */
#define BT_CODEC_LC3_FREQ_44KHZ          BIT(6)
/**
 *  @brief LC3 48 Khz frequency capability
 */
#define BT_CODEC_LC3_FREQ_48KHZ          BIT(7)

/**
 *  @brief LC3 any frequency capability
 */
#define BT_CODEC_LC3_FREQ_ANY            (BT_CODEC_LC3_FREQ_8KHZ | \
					  BT_CODEC_LC3_FREQ_16KHZ | \
					  BT_CODEC_LC3_FREQ_24KHZ)


#define BT_CODEC_CHANNEL1          BIT(0)
#define BT_CODEC_CHANNEL2          BIT(1)
#define BT_CODEC_CHANNEL3          BIT(2)
#define BT_CODEC_CHANNEL4          BIT(3)
#define BT_CODEC_CHANNEL5          BIT(4)
#define BT_CODEC_CHANNEL_SUPPORT (BT_CODEC_CHANNEL1 )
/**
 * @brief Codec capability type id's
 *
 * Used to build and parse codec capabilities as specified in the PAC specification.
 * Source is assigned numbers for Generic Audio, bluetooth.com.
 *
 * Even though they are in-fixed with LC3 they can be used for other codec types as well.
 */
enum bt_codec_capability_type {

	/**
	 *  @brief LC3 sample frequency capability type
	 */
	BT_CODEC_LC3_FREQ                = 0x01,

	/**
	 *  @brief LC3 frame duration capability type
	 */
	BT_CODEC_LC3_DURATION            = 0x02,

	/**
	 *  @brief LC3 channel count capability type
	 */
	BT_CODEC_LC3_CHAN_COUNT          = 0x03,

	/**
	 *  @brief LC3 frame length capability type
	 */
	BT_CODEC_LC3_FRAME_LEN           = 0x04,

	/**
	 *  @brief Max codec frame count per SDU capability type
	 */
	BT_CODEC_LC3_FRAME_COUNT         = 0x05,
};



/**
 *  @brief LC3 7.5 msec frame duration capability
 */
#define BT_CODEC_LC3_DURATION_7_5        BIT(0)
/**
 *  @brief LC3 10 msec frame duration capability
 */
#define BT_CODEC_LC3_DURATION_10         BIT(1)
/**
 *  @brief LC3 any frame duration capability
 */
#define BT_CODEC_LC3_DURATION_ANY        (BT_CODEC_LC3_DURATION_7_5 | \
                                          BT_CODEC_LC3_DURATION_10 | \
					                      BT_CODEC_LC3_DURATION_PREFER_10)
/**
 *  @brief LC3 7.5 msec preferred frame duration capability
 */
#define BT_CODEC_LC3_DURATION_PREFER_7_5 BIT(4)
/**
 *  @brief LC3 10 msec preferred frame duration capability
 */
#define BT_CODEC_LC3_DURATION_PREFER_10  BIT(5)

/**
 *  @brief LC3 minimum supported channel counts
 */
#define BT_CODEC_LC3_CHAN_COUNT_MIN 1
/**
 *  @brief LC3 maximum supported channel counts
 */
#define BT_CODEC_LC3_CHAN_COUNT_MAX 8

/** @brief Audio Context Type for Generic Audio
 *
 * These values are defined by the Generic Audio Assigned Numbers, bluetooth.com
 */
enum bt_audio_context {
	BT_AUDIO_CONTEXT_TYPE_PROHIBITED = 0,
	BT_AUDIO_CONTEXT_TYPE_UNSPECIFIED = BIT(0),
	BT_AUDIO_CONTEXT_TYPE_CONVERSATIONAL = BIT(1),
	BT_AUDIO_CONTEXT_TYPE_MEDIA = BIT(2),
	BT_AUDIO_CONTEXT_TYPE_GAME = BIT(3),
	BT_AUDIO_CONTEXT_TYPE_INSTRUCTIONAL = BIT(4),
	BT_AUDIO_CONTEXT_TYPE_VOICE_ASSISTANTS = BIT(5),
	BT_AUDIO_CONTEXT_TYPE_LIVE = BIT(6),
	BT_AUDIO_CONTEXT_TYPE_SOUND_EFFECTS = BIT(7),
	BT_AUDIO_CONTEXT_TYPE_NOTIFICATIONS = BIT(8),
	BT_AUDIO_CONTEXT_TYPE_RINGTONE = BIT(9),
	BT_AUDIO_CONTEXT_TYPE_ALERTS = BIT(10),
	BT_AUDIO_CONTEXT_TYPE_EMERGENCY_ALARM = BIT(11),
};


#define BT_AUDIO_SNK_CONTEXT_SUPPORT (BT_AUDIO_CONTEXT_TYPE_UNSPECIFIED | \
                                        BT_AUDIO_CONTEXT_TYPE_CONVERSATIONAL | \
                                        BT_AUDIO_CONTEXT_TYPE_MEDIA | \
                                        BT_AUDIO_CONTEXT_TYPE_GAME | \
                                        BT_AUDIO_CONTEXT_TYPE_INSTRUCTIONAL | \
                                        BT_AUDIO_CONTEXT_TYPE_VOICE_ASSISTANTS | \
                                        BT_AUDIO_CONTEXT_TYPE_LIVE  | \
                                        BT_AUDIO_CONTEXT_TYPE_SOUND_EFFECTS | \
                                        BT_AUDIO_CONTEXT_TYPE_NOTIFICATIONS | \
                                        BT_AUDIO_CONTEXT_TYPE_RINGTONE | \
                                        BT_AUDIO_CONTEXT_TYPE_ALERTS | \
                                        BT_AUDIO_CONTEXT_TYPE_EMERGENCY_ALARM)





#define BT_AUDIO_SRC_CONTEXT_SUPPORT    (BT_AUDIO_CONTEXT_TYPE_UNSPECIFIED | \
                                        BT_AUDIO_CONTEXT_TYPE_CONVERSATIONAL | \
                                        BT_AUDIO_CONTEXT_TYPE_MEDIA | \
                                        BT_AUDIO_CONTEXT_TYPE_GAME | \
                                        BT_AUDIO_CONTEXT_TYPE_INSTRUCTIONAL | \
                                        BT_AUDIO_CONTEXT_TYPE_VOICE_ASSISTANTS | \
                                        BT_AUDIO_CONTEXT_TYPE_LIVE  | \
                                        BT_AUDIO_CONTEXT_TYPE_SOUND_EFFECTS | \
                                        BT_AUDIO_CONTEXT_TYPE_NOTIFICATIONS | \
                                        BT_AUDIO_CONTEXT_TYPE_RINGTONE | \
                                        BT_AUDIO_CONTEXT_TYPE_ALERTS | \
                                        BT_AUDIO_CONTEXT_TYPE_EMERGENCY_ALARM)




#define BT_AUDIO_SNK_CONTEXT_AVAILABLE (BT_AUDIO_CONTEXT_TYPE_UNSPECIFIED | \
                                        BT_AUDIO_CONTEXT_TYPE_CONVERSATIONAL | \
                                        BT_AUDIO_CONTEXT_TYPE_MEDIA | \
                                        BT_AUDIO_CONTEXT_TYPE_GAME | \
                                        BT_AUDIO_CONTEXT_TYPE_INSTRUCTIONAL | \
                                        BT_AUDIO_CONTEXT_TYPE_VOICE_ASSISTANTS | \
                                        BT_AUDIO_CONTEXT_TYPE_LIVE  | \
                                        BT_AUDIO_CONTEXT_TYPE_SOUND_EFFECTS | \
                                        BT_AUDIO_CONTEXT_TYPE_NOTIFICATIONS | \
                                        BT_AUDIO_CONTEXT_TYPE_RINGTONE | \
                                        BT_AUDIO_CONTEXT_TYPE_ALERTS | \
                                        BT_AUDIO_CONTEXT_TYPE_EMERGENCY_ALARM)

 #define BT_AUDIO_SRC_CONTEXT_AVAILABLE (BT_AUDIO_CONTEXT_TYPE_UNSPECIFIED | \
                                         BT_AUDIO_CONTEXT_TYPE_CONVERSATIONAL | \
                                         BT_AUDIO_CONTEXT_TYPE_MEDIA | \
                                         BT_AUDIO_CONTEXT_TYPE_GAME | \
                                         BT_AUDIO_CONTEXT_TYPE_INSTRUCTIONAL | \
                                         BT_AUDIO_CONTEXT_TYPE_VOICE_ASSISTANTS | \
                                         BT_AUDIO_CONTEXT_TYPE_LIVE  | \
                                         BT_AUDIO_CONTEXT_TYPE_SOUND_EFFECTS | \
                                         BT_AUDIO_CONTEXT_TYPE_NOTIFICATIONS | \
                                         BT_AUDIO_CONTEXT_TYPE_RINGTONE | \
                                         BT_AUDIO_CONTEXT_TYPE_ALERTS | \
                                         BT_AUDIO_CONTEXT_TYPE_EMERGENCY_ALARM)
                   

/**
 * @brief Codec metadata type IDs
 *
 * Metadata types defined by the Generic Audio assigned numbers (bluetooth.com).
 */
enum bt_audio_metadata_type {
	/** @brief Preferred audio context.
	 *
	 * Bitfield of preferred audio contexts.
	 *
	 * If 0, the context type is not a preferred use case for this codec
	 * configuration.
	 *
	 * See the BT_AUDIO_CONTEXT_* for valid values.
	 */
	BT_AUDIO_METADATA_TYPE_PREF_CONTEXT        = 0x01,

	/** @brief Streaming audio context.
	 *
	 * Bitfield of streaming audio contexts.
	 *
	 * If 0, the context type is not a preferred use case for this codec
	 * configuration.
	 *
	 * See the BT_AUDIO_CONTEXT_* for valid values.
	 */
	BT_AUDIO_METADATA_TYPE_STREAM_CONTEXT      = 0x02,

	/** UTF-8 encoded title or summary of stream content */
	BT_AUDIO_METADATA_TYPE_PROGRAM_INFO        = 0x03,

	/** @brief Stream language
	 *
	 * 3 octet lower case language code defined by ISO 639-3
	 */
	BT_AUDIO_METADATA_TYPE_STREAM_LANG         = 0x04,

	/** Array of 8-bit CCID values */
	BT_AUDIO_METADATA_TYPE_CCID_LIST           = 0x05,

	/** @brief Parental rating
	 *
	 * See @ref bt_audio_parental_rating for valid values.
	 */
	BT_AUDIO_METADATA_TYPE_PARENTAL_RATING     = 0x06,

	/** UTF-8 encoded URI for additional Program information */
	BT_AUDIO_METADATA_TYPE_PROGRAM_INFO_URI    = 0x07,

	/** @brief Audio active state
	 *
	 * See @ref bt_audio_active_state for valid values.
	 */
	BT_AUDIO_METADATA_TYPE_AUDIO_STATE         = 0x08,

	/** Broadcast Audio Immediate Rendering flag  */
	BT_AUDIO_METADATA_TYPE_BROADCAST_IMMEDIATE = 0x09,

	/** Extended metadata */
	BT_AUDIO_METADATA_TYPE_EXTENDED            = 0xFE,

	/** Vendor specific metadata */
	BT_AUDIO_METADATA_TYPE_VENDOR              = 0xFF,
};



struct __PACKED bt_data {
	uint8_t len;
	uint8_t type;
	uint8_t *data;
};


#define CONFIG_BT_CODEC_DATA_COUNT 5
#define CONFIG_BT_CODEC_METADATA_COUNT 1

/** @brief Codec structure. */
struct __PACKED bt_codec {
    /* Number of PAC Records*/ 
    uint8_t  num_pac;    
	/** Codec ID */
	uint8_t  id;
	/** Codec Company ID */
	uint16_t cid;
	/** Codec Company Vendor ID */
	uint16_t vid;
	/** Codec Specific Data count */
	uint8_t   data_count;
	/** Codec Specific Data */
	struct bt_data data[CONFIG_BT_CODEC_DATA_COUNT];
	/** Codec Specific Metadata count */
	uint8_t   meta_count;
	/** Codec Specific Metadata */
	struct bt_data meta[CONFIG_BT_CODEC_METADATA_COUNT];

};


/** @brief Location values for BT Audio.
 *
 * These values are defined by the Generic Audio Assigned Numbers, bluetooth.com
 */
enum bt_audio_location {
	BT_AUDIO_LOCATION_PROHIBITED = 0,
	BT_AUDIO_LOCATION_FRONT_LEFT = BIT(0),
	BT_AUDIO_LOCATION_FRONT_RIGHT = BIT(1),
	BT_AUDIO_LOCATION_FRONT_CENTER = BIT(2),
	BT_AUDIO_LOCATION_LOW_FREQ_EFFECTS_1 = BIT(3),
	BT_AUDIO_LOCATION_BACK_LEFT = BIT(4),
	BT_AUDIO_LOCATION_BACK_RIGHT = BIT(5),
	BT_AUDIO_LOCATION_FRONT_LEFT_OF_CENTER = BIT(6),
	BT_AUDIO_LOCATION_FRONT_RIGHT_OF_CENTER = BIT(7),
	BT_AUDIO_LOCATION_BACK_CENTER = BIT(8),
	BT_AUDIO_LOCATION_LOW_FREQ_EFFECTS_2 = BIT(9),
	BT_AUDIO_LOCATION_SIDE_LEFT = BIT(10),
	BT_AUDIO_LOCATION_SIDE_RIGHT = BIT(11),
	BT_AUDIO_LOCATION_TOP_FRONT_LEFT = BIT(12),
	BT_AUDIO_LOCATION_TOP_FRONT_RIGHT = BIT(13),
	BT_AUDIO_LOCATION_TOP_FRONT_CENTER = BIT(14),
	BT_AUDIO_LOCATION_TOP_CENTER = BIT(15),
	BT_AUDIO_LOCATION_TOP_BACK_LEFT = BIT(16),
	BT_AUDIO_LOCATION_TOP_BACK_RIGHT = BIT(17),
	BT_AUDIO_LOCATION_TOP_SIDE_LEFT = BIT(18),
	BT_AUDIO_LOCATION_TOP_SIDE_RIGHT = BIT(19),
	BT_AUDIO_LOCATION_TOP_BACK_CENTER = BIT(20),
	BT_AUDIO_LOCATION_BOTTOM_FRONT_CENTER = BIT(21),
	BT_AUDIO_LOCATION_BOTTOM_FRONT_LEFT = BIT(22),
	BT_AUDIO_LOCATION_BOTTOM_FRONT_RIGHT = BIT(23),
	BT_AUDIO_LOCATION_FRONT_LEFT_WIDE = BIT(24),
	BT_AUDIO_LOCATION_FRONT_RIGHT_WIDE = BIT(25),
	BT_AUDIO_LOCATION_LEFT_SURROUND = BIT(26),
	BT_AUDIO_LOCATION_RIGHT_SURROUND = BIT(27),
};



#define BT_CODEC_LOCATION_SUPPORT (BT_AUDIO_LOCATION_FRONT_LEFT)


/* ASE Control Point Protocol */
struct __PACKED bt_ascs_ase_cp {
	/* Request/Notification opcode */
	uint8_t  op;
	uint8_t  pdu[0];
};


/* Opcodes */
#define BT_ASCS_CONFIG_OP                0x01

#define BT_ASCS_CONFIG_LATENCY_LOW       0x01
#define BT_ASCS_CONFIG_LATENCY_MEDIUM    0x02
#define BT_ASCS_CONFIG_LATENCY_HIGH      0x03

#define BT_ASCS_CONFIG_PHY_LE_1M         0x01
#define BT_ASCS_CONFIG_PHY_LE_2M         0x02
#define BT_ASCS_CONFIG_PHY_LE_CODED      0x03


struct __PACKED bt_ascs_codec {
	uint8_t  id;
	uint16_t cid;
	uint16_t vid;
};
struct __PACKED bt_ascs_codec_config {
	uint8_t len;
	uint8_t type;
	uint8_t data[0];
};

struct __PACKED bt_ascs_config {
	/* ASE ID */
	uint8_t  ase;
	/* Target latency */
	uint8_t  latency;
	/* Target PHY */
	uint8_t  phy;
	/* Codec ID */
	struct bt_ascs_codec codec;
	/* Codec Specific Config Length */
	uint8_t  cc_len;
	/* LTV-formatted Codec-Specific Configuration */
	struct bt_ascs_codec_config cc[0];
};

struct __PACKED bt_ascs_config_op {
	/* Number of ASEs */
	uint8_t  num_ases;
	/* Config Parameters */
	struct bt_ascs_config cfg[0];
} ;

#define BT_ASCS_QOS_OP                   0x02
struct __PACKED bt_ascs_qos {
	/* ASE ID */
	uint8_t  ase;
	/* CIG ID*/
	uint8_t  cig;
	/* CIG ID*/
	uint8_t  cis;
	/* Frame interval */
	uint8_t  interval[3];
	/* Frame framing */
	uint8_t  framing;
	/* PHY */
	uint8_t  phy;
	/* Maximum SDU Size */
	uint16_t sdu;
	/* Retransmission Effort */
	uint8_t  rtn;
	/* Transport Latency */
	uint16_t latency;
	/* Presentation Delay */
	uint8_t  pd[3];
};

struct __PACKED bt_ascs_qos_op {
	/* Number of ASEs */
	uint8_t  num_ases;
	/* QoS Parameters */
	struct bt_ascs_qos qos[0];
};

#define BT_ASCS_ENABLE_OP                0x03
struct __PACKED bt_ascs_metadata {
	/* ASE ID */
	uint8_t  ase;
	/* Metadata length */
	uint8_t  len;
	/* LTV-formatted Metadata */
	uint8_t  data[0];
};

struct __PACKED bt_ascs_enable_op {
	/* Number of ASEs */
	uint8_t  num_ases;
	/* Metadata */
	struct bt_ascs_metadata metadata[0];
};

#define BT_ASCS_START_OP                 0x04
struct __PACKED bt_ascs_start_op {
	/* Number of ASEs */
	uint8_t  num_ases;
	/* ASE IDs */
	uint8_t  ase[0];
};

#define BT_ASCS_DISABLE_OP               0x05
struct __PACKED bt_ascs_disable_op {
	/* Number of ASEs */
	uint8_t  num_ases;
	/* ASE IDs */
	uint8_t  ase[0];
};

#define BT_ASCS_STOP_OP                  0x06
struct __PACKED bt_ascs_stop_op {
	/* Number of ASEs */
	uint8_t  num_ases;
	/* ASE IDs */
	uint8_t  ase[0];
};

#define BT_ASCS_METADATA_OP              0x07
struct __PACKED bt_ascs_metadata_op {
	/* Number of ASEs */
	uint8_t  num_ases;
	/* Metadata */
	struct bt_ascs_metadata metadata[0];
};

#define BT_ASCS_RELEASE_OP              0x08
struct __PACKED bt_ascs_release_op {
	/* Number of ASEs */
	uint8_t  num_ases;
	/* Ase IDs */
	uint8_t  ase[0];
};

struct __PACKED bt_ascs_cp_ase_rsp {
	/* ASE ID */
	uint8_t  id;
	/* Response code */
	uint8_t  code;
	/* Response reason */
	uint8_t  reason;
};

struct __PACKED bt_ascs_cp_rsp {
	/* Opcode */
	uint8_t  op;
	/* Number of ASEs */
	uint8_t  num_ase;
	/* ASE response */
	struct bt_ascs_cp_ase_rsp ase_rsp[0];
};


/* Response Status Code */
#define BT_ASCS_RSP_SUCCESS              0x00
#define BT_ASCS_RSP_NOT_SUPPORTED        0x01
#define BT_ASCS_RSP_TRUNCATED            0x02
#define BT_ASCS_RSP_INVALID_ASE          0x03
#define BT_ASCS_RSP_INVALID_ASE_STATE    0x04
#define BT_ASCS_RSP_INVALID_DIR          0x05
#define BT_ASCS_RSP_CAP_UNSUPPORTED      0x06
#define BT_ASCS_RSP_CONF_UNSUPPORTED     0x07
#define BT_ASCS_RSP_CONF_REJECTED        0x08
#define BT_ASCS_RSP_CONF_INVALID         0x09
#define BT_ASCS_RSP_METADATA_UNSUPPORTED 0x0a
#define BT_ASCS_RSP_METADATA_REJECTED    0x0b
#define BT_ASCS_RSP_METADATA_INVALID     0x0c
#define BT_ASCS_RSP_NO_MEM               0x0d
#define BT_ASCS_RSP_UNSPECIFIED          0x0e

/* Response Reasons */
#define BT_ASCS_REASON_NONE              0x00
#define BT_ASCS_REASON_CODEC             0x01
#define BT_ASCS_REASON_CODEC_DATA        0x02
#define BT_ASCS_REASON_INTERVAL          0x03
#define BT_ASCS_REASON_FRAMING           0x04
#define BT_ASCS_REASON_PHY               0x05
#define BT_ASCS_REASON_SDU               0x06
#define BT_ASCS_REASON_RTN               0x07
#define BT_ASCS_REASON_LATENCY           0x08
#define BT_ASCS_REASON_PD                0x09
#define BT_ASCS_REASON_CIS               0x0a


/**
 * @brief Codec configuration type IDs
 *
 * Used to build and parse codec configurations as specified in the ASCS and BAP specifications.
 * Source is assigned numbers for Generic Audio, bluetooth.com.
 *
 * Even though they are in-fixed with LC3 they can be used for other codec types as well.
 */
enum bt_codec_config_type {

	/** @brief LC3 Sample Frequency configuration type. */
	BT_CODEC_CONFIG_LC3_FREQ                 = 0x01,

	/** @brief LC3 Frame Duration configuration type. */
	BT_CODEC_CONFIG_LC3_DURATION             = 0x02,

	/** @brief LC3 channel Allocation configuration type. */
	BT_CODEC_CONFIG_LC3_CHAN_ALLOC           = 0x03,

	/** @brief LC3 Frame Length configuration type. */
	BT_CODEC_CONFIG_LC3_FRAME_LEN            = 0x04,

	/** @brief Codec frame blocks, per SDU configuration type. */
	BT_CODEC_CONFIG_LC3_FRAME_BLKS_PER_SDU   = 0x05,
};

/**
 *  @brief 8 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_8KHZ    0x01
/**
 *  @brief 11.025 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_11KHZ   0x02
/**
 *  @brief 16 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_16KHZ   0x03
/**
 *  @brief 22.05 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_22KHZ   0x04
/**
 *  @brief 24 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_24KHZ   0x05
/**
 *  @brief 32 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_32KHZ   0x06
/**
 *  @brief 44.1 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_44KHZ   0x07
/**
 *  @brief 48 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_48KHZ   0x08
/**
 *  @brief 88.2 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_88KHZ   0x09
/**
 *  @brief 96 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_96KHZ   0x0a
/**
 *  @brief 176.4 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_176KHZ   0x0b
/**
 *  @brief 192 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_192KHZ   0x0c
/**
 *  @brief 384 Khz codec Sample Frequency configuration
 */
#define BT_CODEC_CONFIG_LC3_FREQ_384KHZ   0x0d

/**
 *  @brief LC3 7.5 msec Frame Duration configuration
 */
#define BT_CODEC_CONFIG_LC3_DURATION_7_5 0x00
/**
 *  @brief LC3 10 msec Frame Duration configuration
 */
#define BT_CODEC_CONFIG_LC3_DURATION_10  0x01


#define BT_CODEC_CONFIGURED 0x01
#define BT_QOS_CONFIGURED 0x02
#define BT_ENABLING 0x03
#define BT_STREAMING 0x04
#define BT_DISDBLING 0x05



/* ASE_State = 0x01 (Codec Configured), defined in Table 4.3. */
struct __PACKED bt_ascs_ase_status_config {
	uint8_t  framing;
	uint8_t  phy;
	uint8_t  rtn;
	uint16_t latency;
	uint8_t  pd_min[3];
	uint8_t  pd_max[3];
	uint8_t  prefer_pd_min[3];
	uint8_t  prefer_pd_max[3];
	struct bt_ascs_codec codec;
	uint8_t  cc_len;
	/* LTV-formatted Codec-Specific Configuration */
	struct bt_ascs_codec_config cc[0];
};


struct __PACKED bt_ascs_ase_status_config_rsp{
    uint8_t ase_id;
    uint8_t ase_state;
    struct bt_ascs_ase_status_config status_config[0];
};

/* ASE_State = 0x02 (QoS Configured), defined in Table 4.4. */
struct __PACKED bt_ascs_ase_status_qos {
	uint8_t  cig_id;
	uint8_t  cis_id;
	uint8_t  interval[3];
	uint8_t  framing;
	uint8_t  phy;
	uint16_t sdu;
	uint8_t  rtn;
	uint16_t latency;
	uint8_t  pd[3];
};


struct __PACKED bt_ascs_ase_status_qos_rsp{
    uint8_t ase_id;
    uint8_t ase_state;
    struct bt_ascs_ase_status_qos status_qos[0];
};

/* ASE_Status = 0x03 (Enabling) defined in Table 4.5.
 */
struct __PACKED bt_ascs_ase_status_enable {
	uint8_t  cig_id;
	uint8_t  cis_id;
	uint8_t  metadata_len;
	uint8_t  metadata[0];
} ;

struct __PACKED bt_ascs_ase_status_enable_rsp{
    uint8_t ase_id;
    uint8_t ase_state;
    struct bt_ascs_ase_status_enable status_enable[0];
};

/* ASE_Status =  0x04 (Streaming) defined in Table 4.5.
 */
struct __PACKED bt_ascs_ase_status_stream {
	uint8_t  cig_id;
	uint8_t  cis_id;
	uint8_t  metadata_len;
	uint8_t  metadata[0];
} ;

struct __PACKED bt_ascs_ase_status_stream_rsp{
    uint8_t ase_id;
    uint8_t ase_state;
    struct bt_ascs_ase_status_stream status_stream[0];
};

/* ASE_Status = 0x05 (Disabling) as defined in Table 4.5.
 */
struct __PACKED bt_ascs_ase_status_disable {
	uint8_t  cig_id;
	uint8_t  cis_id;
	uint8_t  metadata_len;
	uint8_t  metadata[0];
} ;

/** LE PHY types */
enum {
	/** Convenience macro for when no PHY is set. */
	BT_GAP_LE_PHY_NONE                    = 0,
	/** LE 1M PHY */
	BT_GAP_LE_PHY_1M                      = BIT(0),
	 /** LE 2M PHY */
	BT_GAP_LE_PHY_2M                      = BIT(1),
	/** LE Coded PHY */
	BT_GAP_LE_PHY_CODED                   = BIT(2),
};

/* VCS opcodes */
#define BT_VCP_OPCODE_REL_VOL_DOWN                      0x00
#define BT_VCP_OPCODE_REL_VOL_UP                        0x01
#define BT_VCP_OPCODE_UNMUTE_REL_VOL_DOWN               0x02
#define BT_VCP_OPCODE_UNMUTE_REL_VOL_UP                 0x03
#define BT_VCP_OPCODE_SET_ABS_VOL                       0x04
#define BT_VCP_OPCODE_UNMUTE                            0x05
#define BT_VCP_OPCODE_MUTE                              0x06

struct __PACKED vcs_state {
	uint8_t volume;
	uint8_t mute;
	uint8_t change_counter;
};

struct __PACKED vcs_control {
	uint8_t opcode;
	uint8_t counter;
};

struct __PACKED vcs_control_vol {
	struct vcs_control cp;
	uint8_t volume;
};

/** Volume Control Service Error codes */
#define BT_VCP_ERR_INVALID_COUNTER             0x80
#define BT_VCP_ERR_OP_NOT_SUPPORTED            0x81

/** Volume Control Service Mute Values */
#define BT_VCP_STATE_UNMUTED                   0x00
#define BT_VCP_STATE_MUTED                     0x01


#endif // APP_AUDIO_H_
