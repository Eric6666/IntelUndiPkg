/**************************************************************************

Copyright (c) 2016 - 2021, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/

#ifndef _ICE_SWITCH_H_
#define _ICE_SWITCH_H_

#include "ice_type.h"
#include "ice_protocol_type.h"

#define ICE_SW_CFG_MAX_BUF_LEN 2048
#define ICE_MAX_SW 256
#define ICE_DFLT_VSI_INVAL 0xff

#define ICE_FLTR_RX	BIT(0)
#define ICE_FLTR_TX	BIT(1)
#define ICE_FLTR_RX_LB	BIT(2)
#define ICE_FLTR_TX_RX	(ICE_FLTR_RX | ICE_FLTR_TX)

#if defined(DPDK_SUPPORT) || defined(ADV_AVF_SUPPORT)
/* Switch Profile IDs for Profile related switch rules */
#define ICE_PROFID_IPV4_TCP		4
#define ICE_PROFID_IPV4_UDP		5
#define ICE_PROFID_IPV6_TCP		7
#define ICE_PROFID_IPV6_UDP		8
#endif /* DPDK_SUPPORT || ADV_AVF_SUPPORT */
#ifdef DPDK_SUPPORT
#define ICE_PROFID_PPPOE_PAY		34
#define ICE_PROFID_PPPOE_IPV4_TCP	35
#define ICE_PROFID_PPPOE_IPV4_UDP	36
#define ICE_PROFID_PPPOE_IPV4_OTHER	37
#define ICE_PROFID_PPPOE_IPV6_TCP	38
#define ICE_PROFID_PPPOE_IPV6_UDP	39
#define ICE_PROFID_PPPOE_IPV6_OTHER	40
#endif /* DPDK_SUPPORT */
#define ICE_PROFID_IPV4_GTPC_TEID	41
#define ICE_PROFID_IPV4_GTPC_NO_TEID		42
#define ICE_PROFID_IPV4_GTPU_TEID		43
#define ICE_PROFID_IPV6_GTPC_TEID		44
#define ICE_PROFID_IPV6_GTPC_NO_TEID		45
#define ICE_PROFID_IPV6_GTPU_TEID		46
#ifdef DPDK_SUPPORT
#define ICE_PROFID_IPV4_GTPU_EH_IPV4_OTHER	47
#define ICE_PROFID_IPV4_GTPU_IPV4_OTHER		48
#define ICE_PROFID_IPV4_GTPU_EH_IPV4_UDP	49
#define ICE_PROFID_IPV4_GTPU_IPV4_UDP		50
#define ICE_PROFID_IPV4_GTPU_EH_IPV4_TCP	51
#define ICE_PROFID_IPV4_GTPU_IPV4_TCP		52
#define ICE_PROFID_IPV6_GTPU_EH_IPV4_OTHER	53
#define ICE_PROFID_IPV6_GTPU_IPV4_OTHER		54
#define ICE_PROFID_IPV6_GTPU_EH_IPV4_UDP	55
#define ICE_PROFID_IPV6_GTPU_IPV4_UDP		56
#define ICE_PROFID_IPV6_GTPU_EH_IPV4_TCP	57
#define ICE_PROFID_IPV6_GTPU_IPV4_TCP		58
#define ICE_PROFID_IPV4_GTPU_EH_IPV6_OTHER	59
#define ICE_PROFID_IPV4_GTPU_IPV6_OTHER		60
#define ICE_PROFID_IPV4_GTPU_EH_IPV6_UDP	61
#define ICE_PROFID_IPV4_GTPU_IPV6_UDP		62
#define ICE_PROFID_IPV4_GTPU_EH_IPV6_TCP	63
#define ICE_PROFID_IPV4_GTPU_IPV6_TCP		64
#define ICE_PROFID_IPV6_GTPU_EH_IPV6_OTHER	65
#define ICE_PROFID_IPV6_GTPU_IPV6_OTHER		66
#define ICE_PROFID_IPV6_GTPU_EH_IPV6_UDP	67
#define ICE_PROFID_IPV6_GTPU_IPV6_UDP		68
#define ICE_PROFID_IPV6_GTPU_EH_IPV6_TCP	69
#endif /* DPDK_SUPPORT */
#define ICE_PROFID_IPV6_GTPU_IPV6_TCP		70
#ifdef DPDK_SUPPORT
#define ICE_PROFID_IPV4_ESP		71
#define ICE_PROFID_IPV6_ESP		72
#define ICE_PROFID_IPV4_AH		73
#define ICE_PROFID_IPV6_AH		74
#define ICE_PROFID_IPV4_NAT_T		75
#define ICE_PROFID_IPV6_NAT_T		76
#define ICE_PROFID_MAC_IPV4_L2TPV3	77
#define ICE_PROFID_MAC_IPV6_L2TPV3	78
#define ICE_PROFID_IPV4_PFCP_NODE	79
#define ICE_PROFID_IPV4_PFCP_SESSION	80
#define ICE_PROFID_IPV6_PFCP_NODE	81
#define ICE_PROFID_IPV6_PFCP_SESSION	82
#endif /* DPDK_SUPPORT */

#define DUMMY_ETH_HDR_LEN		16


#ifndef NO_UNUSED_SWITCH_CODE
/* Worst case buffer length for ice_aqc_opc_get_res_alloc */
#define ICE_MAX_RES_TYPES 0x80
#define ICE_AQ_GET_RES_ALLOC_BUF_LEN \
	(ICE_MAX_RES_TYPES * sizeof(struct ice_aqc_get_res_resp_elem))
#endif /* NO_UNUSED_SWITCH_CODE */

#define ICE_VSI_INVAL_ID 0xFFFF
#define ICE_INVAL_Q_HANDLE 0xFFFF

/* VSI context structure for add/get/update/free operations */
struct ice_vsi_ctx {
	u16 vsi_num;
	u16 vsis_allocd;
	u16 vsis_unallocated;
	u16 flags;
	struct ice_aqc_vsi_props info;
	struct ice_sched_vsi_info sched;
	u8 alloc_from_pool;
#ifdef SRIOV_SUPPORT
	u8 vf_num;
#endif /* SRIOV_SUPPORT */
	u16 num_lan_q_entries[ICE_MAX_TRAFFIC_CLASS];
	struct ice_q_ctx *lan_q_ctx[ICE_MAX_TRAFFIC_CLASS];
#ifdef RDMA_SUPPORT
	u16 num_rdma_q_entries[ICE_MAX_TRAFFIC_CLASS];
	struct ice_q_ctx *rdma_q_ctx[ICE_MAX_TRAFFIC_CLASS];
#endif /* RDMA_SUPPORT */
};

#ifndef NO_UNUSED_SWITCH_CODE
/* This is to be used by add/update mirror rule Admin Queue command */
struct ice_mir_rule_buf {
	u16 vsi_idx; /* VSI index */

	/* For each VSI, user can specify whether corresponding VSI
	 * should be added/removed to/from mirror rule
	 *
	 * add mirror rule: this should always be TRUE.
	 * update mirror rule:  add(true) or remove(false) VSI to/from
	 * mirror rule
	 */
	u8 add;
};
#endif /* !NO_UNUSED_SWITCH_CODE */

/* Switch recipe ID enum values are specific to hardware */
enum ice_sw_lkup_type {
	ICE_SW_LKUP_ETHERTYPE = 0,
	ICE_SW_LKUP_MAC = 1,
	ICE_SW_LKUP_MAC_VLAN = 2,
	ICE_SW_LKUP_PROMISC = 3,
	ICE_SW_LKUP_VLAN = 4,
	ICE_SW_LKUP_DFLT = 5,
	ICE_SW_LKUP_ETHERTYPE_MAC = 8,
	ICE_SW_LKUP_PROMISC_VLAN = 9,
#if defined(QV_SUPPORT)
	ICE_SW_LKUP_LPORT = 10,
#endif /* (SWITCH_MODE && !BMSM_MODE) || QV_SUPPORT */
	ICE_SW_LKUP_LAST
};

/* type of filter src ID */
enum ice_src_id {
	ICE_SRC_ID_UNKNOWN = 0,
	ICE_SRC_ID_VSI,
	ICE_SRC_ID_QUEUE,
	ICE_SRC_ID_LPORT,
};

struct ice_fltr_info {
	/* Look up information: how to look up packet */
	enum ice_sw_lkup_type lkup_type;
	/* Forward action: filter action to do after lookup */
	enum ice_sw_fwd_act_type fltr_act;
	/* rule ID returned by firmware once filter rule is created */
	u16 fltr_rule_id;
	u16 flag;

	/* Source VSI for LOOKUP_TX or source port for LOOKUP_RX */
	u16 src;
	enum ice_src_id src_id;

	union {
		struct {
			u8 mac_addr[ETH_ALEN];
		} mac;
		struct {
			u8 mac_addr[ETH_ALEN];
			u16 vlan_id;
		} mac_vlan;
		struct {
			u16 vlan_id;
			u16 tpid;
			u8 tpid_valid;
		} vlan;
		/* Set lkup_type as ICE_SW_LKUP_ETHERTYPE
		 * if just using ethertype as filter. Set lkup_type as
		 * ICE_SW_LKUP_ETHERTYPE_MAC if MAC also needs to be
		 * passed in as filter.
		 */
		struct {
			u16 ethertype;
			u8 mac_addr[ETH_ALEN]; /* optional */
		} ethertype_mac;
	} l_data; /* Make sure to zero out the memory of l_data before using
		   * it or only set the data associated with lookup match
		   * rest everything should be zero
		   */

	/* Depending on filter action */
	union {
		/* queue ID in case of ICE_FWD_TO_Q and starting
		 * queue ID in case of ICE_FWD_TO_QGRP.
		 */
		u16 q_id:11;
		u16 hw_vsi_id:10;
		u16 vsi_list_id:10;
	} fwd_id;

	/* Sw VSI handle */
	u16 vsi_handle;

	/* Set to num_queues if action is ICE_FWD_TO_QGRP. This field
	 * determines the range of queues the packet needs to be forwarded to.
	 * Note that qgrp_size must be set to a power of 2.
	 */
	u8 qgrp_size;

	/* Rule creations populate these indicators basing on the switch type */
	u8 lb_en;	/* Indicate if packet can be looped back */
	u8 lan_en;	/* Indicate if packet can be forwarded to the uplink */
};

#ifdef DVM_SUPPORT
struct ice_update_recipe_lkup_idx_params {
	u16 rid;
	u16 fv_idx;
	bool ignore_valid;
	u16 mask;
	bool mask_valid;
	u8 lkup_idx;
};
#endif /* DVM_SUPPORT */

struct ice_adv_lkup_elem {
	enum ice_protocol_type type;
	union ice_prot_hdr h_u;	/* Header values */
	union ice_prot_hdr m_u;	/* Mask of header values to match */
};

struct entry_vsi_fwd {
	u16 vsi_list;
	u8 list;
	u8 valid;
};

struct entry_to_q {
	u16 q_idx;
	u8 q_region_sz;
	u8 q_pri;
};

struct entry_prune {
	u16 vsi_list;
	u8 list;
	u8 egr;
	u8 ing;
	u8 prune_t;
};

struct entry_mirror {
	u16 mirror_vsi;
};

struct entry_generic_act {
	u16 generic_value;
	u8 offset;
	u8 priority;
};

struct entry_statistics {
	u8 counter_idx;
};

#ifdef DPDK_SUPPORT
union lg_act_entry {
	struct entry_vsi_fwd vsi_fwd;
	struct entry_to_q to_q;
	struct entry_prune prune;
	struct entry_mirror mirror;
	struct entry_generic_act generic_act;
	struct entry_statistics statistics;
};
#endif /* DPDK_SUPPORT */

#ifdef DPDK_SUPPORT
struct ice_prof_type_entry {
	u16 prof_id;
	enum ice_sw_tunnel_type type;
};
#endif

struct ice_sw_act_ctrl {
	/* Source VSI for LOOKUP_TX or source port for LOOKUP_RX */
	u16 src;
	u16 flag;
	enum ice_sw_fwd_act_type fltr_act;
	/* Depending on filter action */
	union {
		/* This is a queue ID in case of ICE_FWD_TO_Q and starting
		 * queue ID in case of ICE_FWD_TO_QGRP.
		 */
		u16 q_id:11;
		u16 vsi_id:10;
		u16 hw_vsi_id:10;
		u16 vsi_list_id:10;
	} fwd_id;
	/* software VSI handle */
	u16 vsi_handle;
	u8 qgrp_size;
#ifdef DPDK_SUPPORT
	u32 markid;
#endif /* DPDK_SUPPORT */
};

struct ice_rule_query_data {
	/* Recipe ID for which the requested rule was added */
	u16 rid;
	/* Rule ID that was added or is supposed to be removed */
	u16 rule_id;
	/* vsi_handle for which Rule was added or is supposed to be removed */
	u16 vsi_handle;
};

/*
 * This structure allows to pass info about lb_en and lan_en
 * flags to ice_add_adv_rule. Values in act would be used
 * only if act_valid was set to true, otherwise dflt
 * values would be used.
 */
struct ice_adv_rule_flags_info {
	u32 act;
	u8 act_valid;		/* indicate if flags in act are valid */
};

struct ice_adv_rule_info {
	enum ice_sw_tunnel_type tun_type;
	struct ice_sw_act_ctrl sw_act;
	u32 priority;
#ifdef LINUX_SUPPORT
	u16 src_vsi;
#endif /* LINUX_SUPPORT */
	u8 rx; /* true means LOOKUP_RX otherwise LOOKUP_TX */
	u8 add_dir_lkup;
	u16 fltr_rule_id;
	u16 lg_id;
	u16 vlan_type;
	struct ice_adv_rule_flags_info flags_info;
};

/* A collection of one or more four word recipe */
struct ice_sw_recipe {
	/* For a chained recipe the root recipe is what should be used for
	 * programming rules
	 */
	u8 is_root;
	u8 root_rid;
	u8 recp_created;

	/* Number of extraction words */
	u8 n_ext_words;
	/* Protocol ID and Offset pair (extraction word) to describe the
	 * recipe
	 */
	struct ice_fv_word ext_words[ICE_MAX_CHAIN_WORDS];
	u16 word_masks[ICE_MAX_CHAIN_WORDS];

	/* if this recipe is a collection of other recipe */
	u8 big_recp;

	/* if this recipe is part of another bigger recipe then chain index
	 * corresponding to this recipe
	 */
	u8 chain_idx;

	/* if this recipe is a collection of other recipe then count of other
	 * recipes and recipe IDs of those recipes
	 */
	u8 n_grp_count;

	/* Bit map specifying the IDs associated with this group of recipe */
	ice_declare_bitmap(r_bitmap, ICE_MAX_NUM_RECIPES);

	enum ice_sw_tunnel_type tun_type;

	/* List of type ice_fltr_mgmt_list_entry or adv_rule */
	u8 adv_rule;
	struct LIST_HEAD_TYPE filt_rules;
	struct LIST_HEAD_TYPE filt_replay_rules;

	struct ice_lock filt_rule_lock;	/* protect filter rule structure */

	/* Profiles this recipe should be associated with */
	struct LIST_HEAD_TYPE fv_list;

	/* Profiles this recipe is associated with */
	u8 num_profs, *prof_ids;

	/* Bit map for possible result indexes */
	ice_declare_bitmap(res_idxs, ICE_MAX_FV_WORDS);

	/* This allows user to specify the recipe priority.
	 * For now, this becomes 'fwd_priority' when recipe
	 * is created, usually recipes can have 'fwd' and 'join'
	 * priority.
	 */
	u8 priority;

	struct LIST_HEAD_TYPE rg_list;

	/* AQ buffer associated with this recipe */
	struct ice_aqc_recipe_data_elem *root_buf;
	/* This struct saves the fv_words for a given lookup */
	struct ice_prot_lkup_ext lkup_exts;
};

/* Bookkeeping structure to hold bitmap of VSIs corresponding to VSI list ID */
struct ice_vsi_list_map_info {
	struct LIST_ENTRY_TYPE list_entry;
	ice_declare_bitmap(vsi_map, ICE_MAX_VSI);
	u16 vsi_list_id;
	/* counter to track how many rules are reusing this VSI list */
	u16 ref_cnt;
};

struct ice_fltr_list_entry {
	struct LIST_ENTRY_TYPE list_entry;
	int status;
	struct ice_fltr_info fltr_info;
};

#ifdef FREEBSD_SUPPORT
/**
 * enum ice_fltr_marker - Marker for syncing OS and driver filter lists
 * @ICE_FLTR_NOT_FOUND: initial state, indicates filter has not been found
 * @ICE_FLTR_FOUND: set when a filter has been found in both lists
 *
 * This enumeration is used to help sync an operating system provided filter
 * list with the filters previously added.
 *
 * This is required for FreeBSD because the operating system does not provide
 * individual indications of whether a filter has been added or deleted, but
 * instead just notifies the driver with the entire new list.
 *
 * To use this marker state, the driver shall initially reset all filters to
 * the ICE_FLTR_NOT_FOUND state. Then, for each filter in the OS list, it
 * shall search the driver list for the filter. If found, the filter state
 * will be set to ICE_FLTR_FOUND. If not found, that filter will be added.
 * Finally, the driver shall search the internal filter list for all filters
 * still marked as ICE_FLTR_NOT_FOUND and remove them.
 */
enum ice_fltr_marker {
	ICE_FLTR_NOT_FOUND,
	ICE_FLTR_FOUND,
};
#endif /* FREEBSD_SUPPORT */

/* This defines an entry in the list that maintains MAC or VLAN membership
 * to HW list mapping, since multiple VSIs can subscribe to the same MAC or
 * VLAN. As an optimization the VSI list should be created only when a
 * second VSI becomes a subscriber to the same MAC address. VSI lists are always
 * used for VLAN membership.
 */
struct ice_fltr_mgmt_list_entry {
	/* back pointer to VSI list ID to VSI list mapping */
	struct ice_vsi_list_map_info *vsi_list_info;
	u16 vsi_count;
#define ICE_INVAL_LG_ACT_INDEX 0xffff
	u16 lg_act_idx;
#define ICE_INVAL_SW_MARKER_ID 0xffff
	u16 sw_marker_id;
	struct LIST_ENTRY_TYPE list_entry;
	struct ice_fltr_info fltr_info;
#define ICE_INVAL_COUNTER_ID 0xff
	u8 counter_index;
#ifdef FREEBSD_SUPPORT
	enum ice_fltr_marker marker;
#endif /* FREEBSD_SUPPORT */
};

struct ice_adv_fltr_mgmt_list_entry {
	struct LIST_ENTRY_TYPE list_entry;

	struct ice_adv_lkup_elem *lkups;
	struct ice_adv_rule_info rule_info;
	u16 lkups_cnt;
	struct ice_vsi_list_map_info *vsi_list_info;
	u16 vsi_count;
};

enum ice_promisc_flags {
	ICE_PROMISC_UCAST_RX = 0,
	ICE_PROMISC_UCAST_TX,
	ICE_PROMISC_MCAST_RX,
	ICE_PROMISC_MCAST_TX,
	ICE_PROMISC_BCAST_RX,
	ICE_PROMISC_BCAST_TX,
	ICE_PROMISC_VLAN_RX,
	ICE_PROMISC_VLAN_TX,
	ICE_PROMISC_UCAST_RX_LB,
	/* Max value */
	ICE_PROMISC_MAX,
};

struct ice_dummy_pkt_offsets {
	enum ice_protocol_type type;
	u16 offset; /* ICE_PROTOCOL_LAST indicates end of list */
};

void
ice_find_dummy_packet(struct ice_adv_lkup_elem *lkups, u16 lkups_cnt,
		      enum ice_sw_tunnel_type tun_type, const u8 **pkt,
		      u16 *pkt_len,
		      const struct ice_dummy_pkt_offsets **offsets);

int
ice_fill_adv_dummy_packet(struct ice_adv_lkup_elem *lkups, u16 lkups_cnt,
			  struct ice_sw_rule_lkup_rx_tx *s_rule,
			  const u8 *dummy_pkt, u16 pkt_len,
			  const struct ice_dummy_pkt_offsets *offsets);

int
ice_add_adv_recipe(struct ice_hw *hw, struct ice_adv_lkup_elem *lkups,
		   u16 lkups_cnt, struct ice_adv_rule_info *rinfo, u16 *rid);

struct ice_adv_fltr_mgmt_list_entry *
ice_find_adv_rule_entry(struct ice_hw *hw, struct ice_adv_lkup_elem *lkups,
			u16 lkups_cnt, u16 recp_id,
			struct ice_adv_rule_info *rinfo);

int
ice_adv_add_update_vsi_list(struct ice_hw *hw,
			    struct ice_adv_fltr_mgmt_list_entry *m_entry,
			    struct ice_adv_rule_info *cur_fltr,
			    struct ice_adv_rule_info *new_fltr);

struct ice_vsi_list_map_info *
ice_find_vsi_list_entry(struct ice_sw_recipe *recp_list, u16 vsi_handle,
			u16 *vsi_list_id);

#ifndef ICE_TDD
/* VSI related commands */
#if !defined(LINUX_SUPPORT) || defined(AE_DRIVER)
int
ice_aq_add_vsi(struct ice_hw *hw, struct ice_vsi_ctx *vsi_ctx,
	       struct ice_sq_cd *cd);
int
ice_aq_free_vsi(struct ice_hw *hw, struct ice_vsi_ctx *vsi_ctx,
		bool keep_vsi_alloc, struct ice_sq_cd *cd);
#endif /* !LINUX_SUPPORT || AE_DRIVER */
#ifndef LINUX_SUPPORT
int
ice_aq_update_vsi(struct ice_hw *hw, struct ice_vsi_ctx *vsi_ctx,
		  struct ice_sq_cd *cd);
#endif /* !LINUX_SUPPORT */
int
ice_add_vsi(struct ice_hw *hw, u16 vsi_handle, struct ice_vsi_ctx *vsi_ctx,
	    struct ice_sq_cd *cd);
int
ice_free_vsi(struct ice_hw *hw, u16 vsi_handle, struct ice_vsi_ctx *vsi_ctx,
	     bool keep_vsi_alloc, struct ice_sq_cd *cd);
int
ice_update_vsi(struct ice_hw *hw, u16 vsi_handle, struct ice_vsi_ctx *vsi_ctx,
	       struct ice_sq_cd *cd);
struct ice_vsi_ctx *ice_get_vsi_ctx(struct ice_hw *hw, u16 vsi_handle);
#ifdef QV_SUPPORT
void ice_clear_vsi_q_ctx(struct ice_hw *hw, u16 vsi_handle);
#endif /* QV_SUPPORT */
void ice_clear_all_vsi_ctx(struct ice_hw *hw);
#ifndef NO_UNUSED_SWITCH_CODE
int
ice_aq_get_vsi_params(struct ice_hw *hw, struct ice_vsi_ctx *vsi_ctx,
		      struct ice_sq_cd *cd);
int
ice_aq_add_update_mir_rule(struct ice_hw *hw, u16 rule_type, u16 dest_vsi,
			   u16 count, struct ice_mir_rule_buf *mr_buf,
			   struct ice_sq_cd *cd, u16 *rule_id);
int
ice_aq_delete_mir_rule(struct ice_hw *hw, u16 rule_id, bool keep_allocd,
		       struct ice_sq_cd *cd);
int
ice_aq_get_storm_ctrl(struct ice_hw *hw, u32 *bcast_thresh, u32 *mcast_thresh,
		      u32 *ctl_bitmask);
int
ice_aq_set_storm_ctrl(struct ice_hw *hw, u32 bcast_thresh, u32 mcast_thresh,
		      u32 ctl_bitmask);
#endif /* !NO_UNUSED_SWITCH_CODE */
/* Switch config */
#ifndef NO_UNUSED_DEBUG_CODE
int
ice_aq_get_sw_cfg(struct ice_hw *hw, struct ice_aqc_get_sw_cfg_resp_elem *buf,
		  u16 buf_size, u16 *req_desc, u16 *num_elems,
		  struct ice_sq_cd *cd);
#endif /* !NO_UNUSED_DEBUG_CODE */
int ice_get_initial_sw_cfg(struct ice_hw *hw);

int
ice_alloc_vlan_res_counter(struct ice_hw *hw, u16 *counter_id);
int
ice_free_vlan_res_counter(struct ice_hw *hw, u16 counter_id);
#ifdef FDIR_SUPPORT
int
ice_alloc_res_cntr(struct ice_hw *hw, u8 type, u8 alloc_shared, u16 num_items,
		   u16 *counter_id);
int
ice_free_res_cntr(struct ice_hw *hw, u8 type, u8 alloc_shared, u16 num_items,
		  u16 counter_id);
#endif /* FDIR_SUPPORT */

#ifdef BMSM_MODE
int ice_update_sw_rule_bridge_mode(struct ice_hw *hw, u8 lport);
#else
int ice_update_sw_rule_bridge_mode(struct ice_hw *hw);
#endif /* BMSM_MODE */
#ifndef NO_UNUSED_SWITCH_CODE
int ice_alloc_rss_global_lut(struct ice_hw *hw, bool shared_res, u16 *global_lut_id);
int ice_free_rss_global_lut(struct ice_hw *hw, u16 global_lut_id);
int
ice_alloc_sw(struct ice_hw *hw, bool ena_stats, bool shared_res, u16 *sw_id,
	     u16 *counter_id);
int
ice_free_sw(struct ice_hw *hw, u16 sw_id, u16 counter_id);
int
ice_aq_get_res_alloc(struct ice_hw *hw, u16 *num_entries,
		     struct ice_aqc_get_res_resp_elem *buf, u16 buf_size,
		     struct ice_sq_cd *cd);
int
ice_aq_get_res_descs(struct ice_hw *hw, u16 num_entries,
		     struct ice_aqc_res_elem *buf, u16 buf_size, u16 res_type,
		     bool res_shared, u16 *desc_id, struct ice_sq_cd *cd);
#endif /* !NO_UNUSED_SWITCH_CODE */
int
ice_add_vlan(struct ice_hw *hw, struct LIST_HEAD_TYPE *m_list);
#ifdef BMSM_MODE
int
ice_add_vlan_on_port(struct ice_hw *hw, struct LIST_HEAD_TYPE *v_list,
		     u8 lport);
int
ice_remove_vlan_on_port(struct ice_hw *hw, struct LIST_HEAD_TYPE *v_list,
			u8 lport);
#endif /* BMSM_MODE */
int ice_remove_vlan(struct ice_hw *hw, struct LIST_HEAD_TYPE *v_list);
#ifndef NO_UNUSED_SWITCH_CODE
void ice_rem_all_sw_rules_info(struct ice_hw *hw);
#endif /* !NO_UNUSED_SWITCH_CODE */
#ifdef BMSM_MODE
int
ice_add_mac_on_port(struct ice_hw *hw, struct LIST_HEAD_TYPE *m_list, u8 lport);
#endif /* BMSM_MODE */
int ice_add_mac(struct ice_hw *hw, struct LIST_HEAD_TYPE *m_lst);
int ice_remove_mac(struct ice_hw *hw, struct LIST_HEAD_TYPE *m_lst);
#ifdef BMSM_MODE
int
ice_remove_mac_on_port(struct ice_hw *hw, struct LIST_HEAD_TYPE *m_list,
		       u8 lport);
#endif /* BMSM_MODE */
#if defined(LINUX_SUPPORT) && defined(ADQ_SUPPORT)
bool ice_mac_fltr_exist(struct ice_hw *hw, u8 *mac, u16 vsi_handle);
bool ice_vlan_fltr_exist(struct ice_hw *hw, u16 vlan_id, u16 vsi_handle);
#endif /* defined(LINUX_SUPPORT) && defined(ADQ_SUPPORT) */
int
ice_add_eth_mac(struct ice_hw *hw, struct LIST_HEAD_TYPE *em_list);
#ifdef BMSM_MODE
int
ice_add_eth_mac_on_port(struct ice_hw *hw, struct LIST_HEAD_TYPE *em_list,
			u8 lport);
int
ice_remove_eth_mac_on_port(struct ice_hw *hw, struct LIST_HEAD_TYPE *em_list,
			   u8 lport);
#endif /* BMSM_MODE */
int
ice_remove_eth_mac(struct ice_hw *hw, struct LIST_HEAD_TYPE *em_list);
#ifndef NO_UNUSED_DEBUG_CODE
void ice_dump_sw_rules(struct ice_hw *hw, enum ice_sw_lkup_type lookup);
#endif /* NO_UNUSED_DEBUG_CODE */
#ifdef RDMA_SUPPORT
int
ice_cfg_iwarp_fltr(struct ice_hw *hw, u16 vsi_handle, bool enable);
#endif /* RDMA_SUPPORT */
#ifndef NO_MACVLAN_SUPPORT
#ifdef BMSM_MODE
int
ice_add_mac_vlan_on_port(struct ice_hw *hw, struct LIST_HEAD_TYPE *mv_list,
			 u8 lport);
int
ice_remove_mac_vlan_on_port(struct ice_hw *hw, struct LIST_HEAD_TYPE *mv_list,
			    u8 lport);
#endif /* BMSM_MODE */
int
ice_add_mac_vlan(struct ice_hw *hw, struct LIST_HEAD_TYPE *m_list);
int
ice_remove_mac_vlan(struct ice_hw *hw, struct LIST_HEAD_TYPE *v_list);
#endif /* !NO_MACVLAN_SUPPORT */

#ifndef NO_UNUSED_SWITCH_CODE
int
ice_add_mac_with_sw_marker(struct ice_hw *hw, struct ice_fltr_info *f_info,
			   u16 sw_marker);
int
ice_add_mac_with_counter(struct ice_hw *hw, struct ice_fltr_info *f_info);
#endif /* !NO_UNUSED_SWITCH_CODE */
void ice_remove_vsi_fltr(struct ice_hw *hw, u16 vsi_handle);
#ifdef BMSM_MODE
void
ice_remove_vsi_fltr_on_port(struct ice_hw *hw, u16 vsi_handle, u8 lport);
#endif /* BMSM_MODE */

#if defined(QV_SUPPORT)
int ice_est_pass_rule_per_port(struct ice_hw *hw,
			       struct ice_port_info *pi);
int ice_trd_pass_rule_per_port(struct ice_hw *hw,
			       struct ice_port_info *pi);
int ice_add_pass_vsi_per_port(struct ice_hw *hw, u16 vsi_handle,
			      struct ice_port_info *pi);
int ice_rem_pass_vsi_per_port(struct ice_hw *hw, u16 vsi_handle,
			      struct ice_port_info *pi);
#endif /* (SWITCH_MODE && !BMSM_MODE) || QV_SUPPORT */
/* Promisc/defport setup for VSIs */
int
ice_cfg_dflt_vsi(struct ice_port_info *pi, u16 vsi_handle, bool set,
		 u8 direction);
bool ice_check_if_dflt_vsi(struct ice_port_info *pi, u16 vsi_handle,
			   bool *rule_exists);
#if defined(BMSM_MODE)
int
ice_set_vsi_promisc_on_port(struct ice_hw *hw, u16 vsi_handle,
			    ice_bitmap_t *promisc_mask, u16 vid, u8 lport);
int
ice_clear_vsi_promisc_on_port(struct ice_hw *hw, u16 vsi_handle,
			      ice_bitmap_t *promisc_mask, u16 vid, u8 lport);
int
ice_set_vlan_vsi_promisc_on_port(struct ice_hw *hw, u16 vsi_handle,
				 ice_bitmap_t *promisc_mask,
				 bool rm_vlan_promisc, u8 lport);
#endif /* BMSM_MODE */
#if !defined(BMSM_MODE) || defined(QV_SUPPORT)
int
ice_set_vsi_promisc(struct ice_hw *hw, u16 vsi_handle,
		    ice_bitmap_t *promisc_mask, u16 vid);
int
ice_clear_vsi_promisc(struct ice_hw *hw, u16 vsi_handle,
		      ice_bitmap_t *promisc_mask, u16 vid);
int
ice_set_vlan_vsi_promisc(struct ice_hw *hw, u16 vsi_handle,
			 ice_bitmap_t *promisc_mask, bool rm_vlan_promisc);
#endif /* !BMSM_MODE || QV_SUPPORT */

#if !defined(NO_UNUSED_SWITCH_CODE) || defined(DPDK_SUPPORT)
/* Get VSIs Promisc/defport settings */
#if defined(BMSM_MODE)
int
ice_get_vsi_promisc_on_port(struct ice_hw *hw, u16 vsi_handle,
			    ice_bitmap_t *promisc_mask, u16 *vid, u8 lport);
int
ice_get_vsi_vlan_promisc_on_port(struct ice_hw *hw, u16 vsi_handle,
				 ice_bitmap_t *promisc_mask, u16 *vid,
				 u8 lport);
#endif /* BMSM_MODE */
#if !defined(BMSM_MODE) || defined(QV_SUPPORT)
int
ice_get_vsi_promisc(struct ice_hw *hw, u16 vsi_handle,
		    ice_bitmap_t *promisc_mask, u16 *vid);
int
ice_get_vsi_vlan_promisc(struct ice_hw *hw, u16 vsi_handle,
			 ice_bitmap_t *promisc_mask, u16 *vid);
#endif /* !BMSM_MODE || QV_SUPPORT */
#endif /* !NO_UNUSED_SWITCH_CODE || DPDK_SUPPORT */

#ifndef NO_ADV_SW_SUPPORT
int
ice_aq_add_recipe(struct ice_hw *hw,
		  struct ice_aqc_recipe_data_elem *s_recipe_list,
		  u16 num_recipes, struct ice_sq_cd *cd);

int
ice_aq_get_recipe(struct ice_hw *hw,
		  struct ice_aqc_recipe_data_elem *s_recipe_list,
		  u16 *num_recipes, u16 recipe_root, struct ice_sq_cd *cd);
int
ice_aq_map_recipe_to_profile(struct ice_hw *hw, u32 profile_id, u8 *r_bitmap,
			     struct ice_sq_cd *cd);

int
ice_aq_get_recipe_to_profile(struct ice_hw *hw, u32 profile_id, u8 *r_bitmap,
			     struct ice_sq_cd *cd);

void ice_init_chk_subscribable_recipe_support(struct ice_hw *hw);

int ice_alloc_recipe(struct ice_hw *hw, u16 *recipe_id);
#ifdef LINUX_SUPPORT
/* these are only here to make the linux driver build for CI */
static inline void ice_rule_add_tunnel_metadata(struct ice_adv_lkup_elem *lkup,
						struct ice_adv_rule_info *rule_info,
						enum ice_sw_tunnel_type tun_type) {}
static inline void ice_rule_add_direction_metadata(struct ice_adv_lkup_elem *lkup) {}
#ifdef HAVE_TCF_VLAN_TPID
static inline void ice_rule_add_vlan_metadata(struct ice_adv_lkup_elem *lkup) {}
#endif /* HAVE_TCF_VLAN_TPID */
static inline void ice_rule_add_src_vsi_metadata(struct ice_adv_lkup_elem *lkup) {}
#endif /* LINUX_SUPPORT */
int
ice_add_adv_rule(struct ice_hw *hw, struct ice_adv_lkup_elem *lkups,
		 u16 lkups_cnt, struct ice_adv_rule_info *rinfo,
		 struct ice_rule_query_data *added_entry);
int
ice_rem_adv_rule_for_vsi(struct ice_hw *hw, u16 vsi_handle);
int
ice_rem_adv_rule_by_id(struct ice_hw *hw,
		       struct ice_rule_query_data *remove_entry);
int
ice_rem_adv_rule(struct ice_hw *hw, struct ice_adv_lkup_elem *lkups,
		 u16 lkups_cnt, struct ice_adv_rule_info *rinfo);
#endif /* !NO_ADV_SW_SUPPORT */

#ifndef NO_UNUSED_DEBUG_CODE
int ice_dump_sw_cfg(struct ice_hw *hw);
#endif /* NO_UNUSED_DEBUG_CODE */
#ifndef LINUX_SUPPORT
int ice_replay_all_fltr(struct ice_hw *hw);
#endif /* !LINUX_SUPPORT */

int
ice_init_def_sw_recp(struct ice_hw *hw, struct ice_sw_recipe **recp_list);
u16 ice_get_hw_vsi_num(struct ice_hw *hw, u16 vsi_handle);
bool ice_is_vsi_valid(struct ice_hw *hw, u16 vsi_handle);
#endif /* !ICE_TDD */

int
ice_replay_vsi_all_fltr(struct ice_hw *hw, struct ice_port_info *pi,
			u16 vsi_handle);
void ice_rm_sw_replay_rule_info(struct ice_hw *hw, struct ice_switch_info *sw);
void ice_rm_all_sw_replay_rule_info(struct ice_hw *hw);
#ifdef DPDK_SUPPORT
bool ice_is_prof_rule(enum ice_sw_tunnel_type type);
#endif /* DPDK_SUPPORT */
#if defined(LINUX_SUPPORT) && defined(DCF_SUPPORT) || defined(ESWITCH_SUPPORT) || defined(RDMA_SUPPORT)
int
ice_aq_sw_rules(struct ice_hw *hw, void *rule_list, u16 rule_list_sz,
		u8 num_rules, enum ice_adminq_opc opc, struct ice_sq_cd *cd);
#endif /* LINUX_SUPPORT && DCF_SUPPORT || ESWITCH_SUPPORT || RDMA_SUPPORT */
#ifdef DVM_SUPPORT
int
ice_update_recipe_lkup_idx(struct ice_hw *hw,
			   struct ice_update_recipe_lkup_idx_params *params);
void ice_change_proto_id_to_dvm(void);
#endif /* DVM_SUPPORT */
#endif /* _ICE_SWITCH_H_ */
