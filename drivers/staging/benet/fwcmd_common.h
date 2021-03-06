/*
 * Copyright (C) 2005 - 2008 ServerEngines
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.  The full GNU General
 * Public License is included in this distribution in the file called COPYING.
 *
 * Contact Information:
 * linux-drivers@serverengines.com
 *
 * ServerEngines
 * 209 N. Fair Oaks Ave
 * Sunnyvale, CA 94085
 */
/*
 * Autogenerated by srcgen version: 0127
 */
#ifndef __fwcmd_common_amap_h__
#define __fwcmd_common_amap_h__
#include "host_struct.h"

/* --- PHY_LINK_DUPLEX_ENUM --- */
#define PHY_LINK_DUPLEX_NONE            (0)
#define PHY_LINK_DUPLEX_HALF            (1)
#define PHY_LINK_DUPLEX_FULL            (2)

/* --- PHY_LINK_SPEED_ENUM --- */
#define PHY_LINK_SPEED_ZERO             (0)	/* No link. */
#define PHY_LINK_SPEED_10MBPS           (1)	/* 10 Mbps */
#define PHY_LINK_SPEED_100MBPS          (2)	/* 100 Mbps */
#define PHY_LINK_SPEED_1GBPS            (3)	/* 1 Gbps */
#define PHY_LINK_SPEED_10GBPS           (4)	/* 10 Gbps */

/* --- PHY_LINK_FAULT_ENUM --- */
#define PHY_LINK_FAULT_NONE             (0)	/* No fault status
							available or detected */
#define PHY_LINK_FAULT_LOCAL            (1)	/* Local fault detected */
#define PHY_LINK_FAULT_REMOTE           (2)	/* Remote fault detected */

/* --- BE_ULP_MASK --- */
#define BE_ULP0_MASK                    (1)
#define BE_ULP1_MASK                    (2)
#define BE_ULP2_MASK                    (4)

/* --- NTWK_ACTIVE_PORT --- */
#define NTWK_PORT_A                     (0)	/* Port A is currently active */
#define NTWK_PORT_B                     (1)	/* Port B is currently active */
#define NTWK_NO_ACTIVE_PORT             (15)	/* Both ports have lost link */

/* --- NTWK_LINK_TYPE --- */
#define NTWK_LINK_TYPE_PHYSICAL         (0)	/* link up/down event
						   applies to BladeEngine's
						   Physical Ports
						   */
#define NTWK_LINK_TYPE_VIRTUAL          (1)	/* Virtual link up/down event
						   reported by BladeExchange.
						   This applies only when the
						   VLD feature is enabled
						   */

/*
 * --- FWCMD_MAC_TYPE_ENUM ---
 * This enum defines the types of MAC addresses in the RXF MAC Address Table.
 */
#define MAC_ADDRESS_TYPE_STORAGE        (0)	/* Storage MAC Address */
#define MAC_ADDRESS_TYPE_NETWORK        (1)	/* Network MAC Address */
#define MAC_ADDRESS_TYPE_PD             (2)	/* Protection Domain MAC Addr */
#define MAC_ADDRESS_TYPE_MANAGEMENT     (3)	/* Managment MAC Address */


/* --- FWCMD_RING_TYPE_ENUM --- */
#define FWCMD_RING_TYPE_ETH_RX          (1)	/* Ring created with */
					/* FWCMD_COMMON_ETH_RX_CREATE. */
#define FWCMD_RING_TYPE_ETH_TX          (2)	/* Ring created with */
					/* FWCMD_COMMON_ETH_TX_CREATE. */
#define FWCMD_RING_TYPE_ISCSI_WRBQ      (3)	/* Ring created with */
					/* FWCMD_COMMON_ISCSI_WRBQ_CREATE. */
#define FWCMD_RING_TYPE_ISCSI_DEFQ      (4)	/* Ring created with */
					/* FWCMD_COMMON_ISCSI_DEFQ_CREATE. */
#define FWCMD_RING_TYPE_TPM_WRBQ        (5)	/* Ring created with */
					/* FWCMD_COMMON_TPM_WRBQ_CREATE. */
#define FWCMD_RING_TYPE_TPM_DEFQ        (6)	/* Ring created with */
					/* FWCMD_COMMONTPM_TDEFQ_CREATE. */
#define FWCMD_RING_TYPE_TPM_RQ          (7)	/* Ring created with */
					/* FWCMD_COMMON_TPM_RQ_CREATE. */
#define FWCMD_RING_TYPE_MCC             (8)	/* Ring created with */
					/* FWCMD_COMMON_MCC_CREATE. */
#define FWCMD_RING_TYPE_CQ              (9)	/* Ring created with */
					/* FWCMD_COMMON_CQ_CREATE. */
#define FWCMD_RING_TYPE_EQ              (10)	/* Ring created with */
					/* FWCMD_COMMON_EQ_CREATE. */
#define FWCMD_RING_TYPE_QP              (11)	/* Ring created with */
					/* FWCMD_RDMA_QP_CREATE. */


/* --- ETH_TX_RING_TYPE_ENUM --- */
#define ETH_TX_RING_TYPE_FORWARDING     (1)	/* Ethernet ring for
						   forwarding packets */
#define ETH_TX_RING_TYPE_STANDARD       (2)	/* Ethernet ring for sending
						   network packets. */
#define ETH_TX_RING_TYPE_BOUND          (3)	/* Ethernet ring bound to the
						   port specified in the command
						   header.port_number field.
						   Rings of this type are
						   NOT subject to the
						   failover logic implemented
						   in the BladeEngine.
						   */

/* --- FWCMD_COMMON_QOS_TYPE_ENUM --- */
#define QOS_BITS_NIC                    (1)	/* max_bits_per_second_NIC */
						  /* field is valid.  */
#define QOS_PKTS_NIC                    (2)	/* max_packets_per_second_NIC */
						  /* field is valid.  */
#define QOS_IOPS_ISCSI                  (4)	/* max_ios_per_second_iSCSI */
						  /*field is valid.  */
#define QOS_VLAN_TAG                    (8)	/* domain_VLAN_tag field
						   is valid. */
#define QOS_FABRIC_ID                   (16)	/* fabric_domain_ID field
						   is valid. */
#define QOS_OEM_PARAMS                  (32)	/* qos_params_oem field
						   is valid. */
#define QOS_TPUT_ISCSI                  (64)	/* max_bytes_per_second_iSCSI
						   field  is valid.  */


/*
 * --- FAILOVER_CONFIG_ENUM ---
 * Failover configuration setting used in FWCMD_COMMON_FORCE_FAILOVER
 */
#define FAILOVER_CONFIG_NO_CHANGE       (0)	/* No change to automatic */
						  /* port failover setting. */
#define FAILOVER_CONFIG_ON              (1)	/* Automatic port failover
						   on link down  is enabled. */
#define FAILOVER_CONFIG_OFF             (2)	/* Automatic port failover
						   on link down is disabled. */

/*
 * --- FAILOVER_PORT_ENUM ---
 * Failover port setting used in FWCMD_COMMON_FORCE_FAILOVER
 */
#define FAILOVER_PORT_A                 (0)	/* Selects port A. */
#define FAILOVER_PORT_B                 (1)	/* Selects port B. */
#define FAILOVER_PORT_NONE              (15)	/* No port change requested. */


/*
 * --- MGMT_FLASHROM_OPCODE ---
 * Flash ROM operation code
 */
#define MGMT_FLASHROM_OPCODE_FLASH      (1)	/* Commit downloaded data
						   to Flash ROM */
#define MGMT_FLASHROM_OPCODE_SAVE       (2)	/* Save downloaded data to
						   ARM's DDR - do not flash */
#define MGMT_FLASHROM_OPCODE_CLEAR      (3)	/* Erase specified component
						   from FlashROM */
#define MGMT_FLASHROM_OPCODE_REPORT     (4)	/* Read specified component
						   from Flash ROM */
#define MGMT_FLASHROM_OPCODE_IMAGE_INFO (5)	/* Returns size of a
						   component */

/*
 * --- MGMT_FLASHROM_OPTYPE ---
 * Flash ROM operation type
 */
#define MGMT_FLASHROM_OPTYPE_CODE_FIRMWARE (0)	/* Includes ARM firmware,
						   IPSec (optional) and EP
						   firmware  */
#define MGMT_FLASHROM_OPTYPE_CODE_REDBOOT (1)
#define MGMT_FLASHROM_OPTYPE_CODE_BIOS  (2)
#define MGMT_FLASHROM_OPTYPE_CODE_PXE_BIOS (3)
#define MGMT_FLASHROM_OPTYPE_CODE_CTRLS (4)
#define MGMT_FLASHROM_OPTYPE_CFG_IPSEC  (5)
#define MGMT_FLASHROM_OPTYPE_CFG_INI    (6)
#define MGMT_FLASHROM_OPTYPE_ROM_OFFSET_SPECIFIED (7)

/*
 * --- FLASHROM_TYPE ---
 * Flash ROM manufacturers supported in the f/w
 */
#define INTEL                           (0)
#define SPANSION                        (1)
#define MICRON                          (2)

/* --- DDR_CAS_TYPE --- */
#define CAS_3                           (0)
#define CAS_4                           (1)
#define CAS_5                           (2)

/* --- DDR_SIZE_TYPE --- */
#define SIZE_256MB                      (0)
#define SIZE_512MB                      (1)

/* --- DDR_MODE_TYPE --- */
#define DDR_NO_ECC                      (0)
#define DDR_ECC                         (1)

/* --- INTERFACE_10GB_TYPE --- */
#define CX4_TYPE                        (0)
#define XFP_TYPE                        (1)

/* --- BE_CHIP_MAX_MTU --- */
#define CHIP_MAX_MTU                    (9000)

/* --- XAUI_STATE_ENUM --- */
#define XAUI_STATE_ENABLE               (0)	/* This MUST be the default
						   value for all requests
						   which set/change
						   equalization parameter.  */
#define XAUI_STATE_DISABLE              (255)	/* The XAUI for both ports
						   may be disabled for EMI
						   tests. There is no
						   provision for turning off
						   individual ports.
						   */
/* --- BE_ASIC_REVISION --- */
#define BE_ASIC_REV_A0                  (1)
#define BE_ASIC_REV_A1                  (2)

#endif /* __fwcmd_common_amap_h__ */
