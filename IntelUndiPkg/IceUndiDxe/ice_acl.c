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

#ifndef NO_ACL_SUPPORT
#include "ice_acl.h"
#include "ice_adminq_cmd.h"

/**
 * ice_aq_alloc_acl_tbl - allocate ACL table
 * @hw: pointer to the HW struct
 * @tbl: pointer to ice_acl_alloc_tbl struct
 * @cd: pointer to command details structure or NULL
 *
 * Allocate ACL table (indirect 0x0C10)
 */
int
ice_aq_alloc_acl_tbl(struct ice_hw *hw, struct ice_acl_alloc_tbl *tbl,
		     struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_alloc_table *cmd;
	struct ice_aq_desc desc;

	if (!tbl->act_pairs_per_entry)
		return ICE_ERR_PARAM;

	if (tbl->act_pairs_per_entry > ICE_AQC_MAX_ACTION_MEMORIES)
		return ICE_ERR_MAX_LIMIT;

	/* If this is concurrent table, then buffer shall be valid and
	 * contain DependentAllocIDs, 'num_dependent_alloc_ids' should be valid
	 * and within limit
	 */
	if (tbl->concurr) {
		if (!tbl->num_dependent_alloc_ids)
			return ICE_ERR_PARAM;
		if (tbl->num_dependent_alloc_ids >
		    ICE_AQC_MAX_CONCURRENT_ACL_TBL)
			return ICE_ERR_INVAL_SIZE;
	}

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_alloc_acl_tbl);
	desc.flags |= CPU_TO_LE16(ICE_AQ_FLAG_RD);

	cmd = &desc.params.alloc_table;
	cmd->table_width = CPU_TO_LE16(tbl->width * BITS_PER_BYTE);
	cmd->table_depth = CPU_TO_LE16(tbl->depth);
	cmd->act_pairs_per_entry = tbl->act_pairs_per_entry;
	if (tbl->concurr)
		cmd->table_type = tbl->num_dependent_alloc_ids;

	return ice_aq_send_cmd(hw, &desc, &tbl->buf, sizeof(tbl->buf), cd);
}

/**
 * ice_aq_dealloc_acl_tbl - deallocate ACL table
 * @hw: pointer to the HW struct
 * @alloc_id: allocation ID of the table being released
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Deallocate ACL table (indirect 0x0C11)
 *
 * NOTE: This command has no buffer format for command itself but response
 * format is 'struct ice_aqc_acl_generic', pass ptr to that struct
 * as 'buf' and its size as 'buf_size'
 */
int
ice_aq_dealloc_acl_tbl(struct ice_hw *hw, u16 alloc_id,
		       struct ice_aqc_acl_generic *buf, struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_tbl_actpair *cmd;
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_dealloc_acl_tbl);
	cmd = &desc.params.tbl_actpair;
	cmd->alloc_id = CPU_TO_LE16(alloc_id);

	return ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
}

static int
ice_aq_acl_entry(struct ice_hw *hw, u16 opcode, u8 tcam_idx, u16 entry_idx,
		 struct ice_aqc_acl_data *buf, struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_entry *cmd;
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, opcode);

	if (opcode == ice_aqc_opc_program_acl_entry)
		desc.flags |= CPU_TO_LE16(ICE_AQ_FLAG_RD);

	cmd = &desc.params.program_query_entry;
	cmd->tcam_index = tcam_idx;
	cmd->entry_index = CPU_TO_LE16(entry_idx);

	return ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
}

/**
 * ice_aq_program_acl_entry - program ACL entry
 * @hw: pointer to the HW struct
 * @tcam_idx: Updated TCAM block index
 * @entry_idx: updated entry index
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Program ACL entry (direct 0x0C20)
 */
int
ice_aq_program_acl_entry(struct ice_hw *hw, u8 tcam_idx, u16 entry_idx,
			 struct ice_aqc_acl_data *buf, struct ice_sq_cd *cd)
{
	return ice_aq_acl_entry(hw, ice_aqc_opc_program_acl_entry, tcam_idx,
				entry_idx, buf, cd);
}

#if defined(ACL_DEBUG) || !defined(NO_UNUSED_PACKAGE_CODE)
/**
 * ice_aq_query_acl_entry - query ACL entry
 * @hw: pointer to the HW struct
 * @tcam_idx: Updated TCAM block index
 * @entry_idx: updated entry index
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Query ACL entry (direct 0x0C24)
 *
 * NOTE: Caller of this API to parse 'buf' appropriately since it contains
 * response (key and key invert)
 */
int
ice_aq_query_acl_entry(struct ice_hw *hw, u8 tcam_idx, u16 entry_idx,
		       struct ice_aqc_acl_data *buf, struct ice_sq_cd *cd)
{
	return ice_aq_acl_entry(hw, ice_aqc_opc_query_acl_entry, tcam_idx,
				entry_idx, buf, cd);
}
#endif /* ACL_DEBUG || !NO_UNUSED_PACKAGE_CODE */

#ifndef NO_UNUSED_PACKAGE_CODE
/* Helper function to alloc/dealloc ACL action pair */
static int
ice_aq_actpair_a_d(struct ice_hw *hw, u16 opcode, u16 alloc_id,
		   struct ice_aqc_acl_generic *buf, struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_tbl_actpair *cmd;
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, opcode);
	cmd = &desc.params.tbl_actpair;
	cmd->alloc_id = CPU_TO_LE16(alloc_id);

	return ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
}

/**
 * ice_aq_alloc_actpair - allocate actionpair for specified ACL table
 * @hw: pointer to the HW struct
 * @alloc_id: allocation ID of the table being associated with the actionpair
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Allocate ACL actionpair (direct 0x0C12)
 *
 * This command doesn't need and doesn't have its own command buffer
 * but for response format is as specified in 'struct ice_aqc_acl_generic'
 */
int
ice_aq_alloc_actpair(struct ice_hw *hw, u16 alloc_id,
		     struct ice_aqc_acl_generic *buf, struct ice_sq_cd *cd)
{
	return ice_aq_actpair_a_d(hw, ice_aqc_opc_alloc_acl_actpair, alloc_id,
				  buf, cd);
}

/**
 * ice_aq_dealloc_actpair - dealloc actionpair for specified ACL table
 * @hw: pointer to the HW struct
 * @alloc_id: allocation ID of the table being associated with the actionpair
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 *  Deallocate ACL actionpair (direct 0x0C13)
 */
int
ice_aq_dealloc_actpair(struct ice_hw *hw, u16 alloc_id,
		       struct ice_aqc_acl_generic *buf, struct ice_sq_cd *cd)
{
	return ice_aq_actpair_a_d(hw, ice_aqc_opc_dealloc_acl_actpair, alloc_id,
				  buf, cd);
}
#endif /* !NO_UNUSED_PACKAGE_CODE */

/* Helper function to program/query ACL action pair */
static int
ice_aq_actpair_p_q(struct ice_hw *hw, u16 opcode, u8 act_mem_idx,
		   u16 act_entry_idx, struct ice_aqc_actpair *buf,
		   struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_actpair *cmd;
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, opcode);

	if (opcode == ice_aqc_opc_program_acl_actpair)
		desc.flags |= CPU_TO_LE16(ICE_AQ_FLAG_RD);

	cmd = &desc.params.program_query_actpair;
	cmd->act_mem_index = act_mem_idx;
	cmd->act_entry_index = CPU_TO_LE16(act_entry_idx);

	return ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
}

/**
 * ice_aq_program_actpair - program ACL actionpair
 * @hw: pointer to the HW struct
 * @act_mem_idx: action memory index to program/update/query
 * @act_entry_idx: the entry index in action memory to be programmed/updated
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Program action entries (indirect 0x0C1C)
 */
int
ice_aq_program_actpair(struct ice_hw *hw, u8 act_mem_idx, u16 act_entry_idx,
		       struct ice_aqc_actpair *buf, struct ice_sq_cd *cd)
{
	return ice_aq_actpair_p_q(hw, ice_aqc_opc_program_acl_actpair,
				  act_mem_idx, act_entry_idx, buf, cd);
}

#if defined(ACL_DEBUG) || !defined(NO_UNUSED_PACKAGE_CODE)
/**
 * ice_aq_query_actpair - query ACL actionpair
 * @hw: pointer to the HW struct
 * @act_mem_idx: action memory index to program/update/query
 * @act_entry_idx: the entry index in action memory to be programmed/updated
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Query ACL actionpair (indirect 0x0C25)
 */
int
ice_aq_query_actpair(struct ice_hw *hw, u8 act_mem_idx, u16 act_entry_idx,
		     struct ice_aqc_actpair *buf, struct ice_sq_cd *cd)
{
	return ice_aq_actpair_p_q(hw, ice_aqc_opc_query_acl_actpair,
				  act_mem_idx, act_entry_idx, buf, cd);
}
#endif /* ACL_DEBUG || !NO_UNUSED_PACKAGE_CODE */

#ifndef NO_UNUSED_PACKAGE_CODE
/**
 * ice_aq_dealloc_acl_res - deallocate ACL resources
 * @hw: pointer to the HW struct
 * @cd: pointer to command details structure or NULL
 *
 * De-allocate ACL resources (direct 0x0C1A). Used by SW to release all the
 * resources allocated for it using a single command
 */
int ice_aq_dealloc_acl_res(struct ice_hw *hw, struct ice_sq_cd *cd)
{
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_dealloc_acl_res);

	return ice_aq_send_cmd(hw, &desc, NULL, 0, cd);
}
#endif /* NO_UNUSED_PACKAGE_CODE */

/**
 * ice_acl_prof_aq_send - sending ACL profile AQ commands
 * @hw: pointer to the HW struct
 * @opc: command opcode
 * @prof_id: profile ID
 * @buf: ptr to buffer
 * @cd: pointer to command details structure or NULL
 *
 * This function sends ACL profile commands
 */
static int
ice_acl_prof_aq_send(struct ice_hw *hw, u16 opc, u8 prof_id,
		     struct ice_aqc_acl_prof_generic_frmt *buf,
		     struct ice_sq_cd *cd)
{
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, opc);
	desc.params.profile.profile_id = prof_id;
	if (opc == ice_aqc_opc_program_acl_prof_extraction ||
	    opc == ice_aqc_opc_program_acl_prof_ranges)
		desc.flags |= CPU_TO_LE16(ICE_AQ_FLAG_RD);
	return ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
}

/**
 * ice_prgm_acl_prof_xtrct - program ACL profile extraction sequence
 * @hw: pointer to the HW struct
 * @prof_id: profile ID
 * @buf: ptr to buffer
 * @cd: pointer to command details structure or NULL
 *
 * Program ACL profile extraction (indirect 0x0C1D)
 */
int
ice_prgm_acl_prof_xtrct(struct ice_hw *hw, u8 prof_id,
			struct ice_aqc_acl_prof_generic_frmt *buf,
			struct ice_sq_cd *cd)
{
	return ice_acl_prof_aq_send(hw, ice_aqc_opc_program_acl_prof_extraction,
				    prof_id, buf, cd);
}

/**
 * ice_query_acl_prof - query ACL profile
 * @hw: pointer to the HW struct
 * @prof_id: profile ID
 * @buf: ptr to buffer (which will contain response of this command)
 * @cd: pointer to command details structure or NULL
 *
 * Query ACL profile (indirect 0x0C21)
 */
int
ice_query_acl_prof(struct ice_hw *hw, u8 prof_id,
		   struct ice_aqc_acl_prof_generic_frmt *buf,
		   struct ice_sq_cd *cd)
{
	return ice_acl_prof_aq_send(hw, ice_aqc_opc_query_acl_prof, prof_id,
				    buf, cd);
}

/**
 * ice_aq_acl_cntrs_chk_params - Checks ACL counter parameters
 * @cntrs: ptr to buffer describing input and output params
 *
 * This function checks the counter bank range for counter type and returns
 * success or failure.
 */
static int ice_aq_acl_cntrs_chk_params(struct ice_acl_cntrs *cntrs)
{
	int status = 0;

	if (!cntrs || !cntrs->amount)
		return ICE_ERR_PARAM;

	switch (cntrs->type) {
	case ICE_AQC_ACL_CNT_TYPE_SINGLE:
		/* Single counter type - configured to count either bytes
		 * or packets, the valid values for byte or packet counters
		 * shall be 0-3.
		 */
		if (cntrs->bank > ICE_AQC_ACL_MAX_CNT_SINGLE)
			status = ICE_ERR_OUT_OF_RANGE;
		break;
	case ICE_AQC_ACL_CNT_TYPE_DUAL:
		/* Pair counter type - counts number of bytes and packets
		 * The valid values for byte/packet counter duals shall be 0-1
		 */
		if (cntrs->bank > ICE_AQC_ACL_MAX_CNT_DUAL)
			status = ICE_ERR_OUT_OF_RANGE;
		break;
	default:
		/* Unspecified counter type - Invalid or error */
		status = ICE_ERR_PARAM;
	}

	return status;
}

/**
 * ice_aq_alloc_acl_cntrs - allocate ACL counters
 * @hw: pointer to the HW struct
 * @cntrs: ptr to buffer describing input and output params
 * @cd: pointer to command details structure or NULL
 *
 * Allocate ACL counters (indirect 0x0C16). This function attempts to
 * allocate a contiguous block of counters. In case of failures, caller can
 * attempt to allocate a smaller chunk. The allocation is considered
 * unsuccessful if returned counter value is invalid. In this case it returns
 * an error otherwise success.
 */
int
ice_aq_alloc_acl_cntrs(struct ice_hw *hw, struct ice_acl_cntrs *cntrs,
		       struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_alloc_counters *cmd;
	u16 first_cntr, last_cntr;
	struct ice_aq_desc desc;
	int status;

	/* check for invalid params */
	status = ice_aq_acl_cntrs_chk_params(cntrs);
	if (status)
		return status;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_alloc_acl_counters);
	cmd = &desc.params.alloc_counters;
	cmd->counter_amount = cntrs->amount;
	cmd->counters_type = cntrs->type;
	cmd->bank_alloc = cntrs->bank;
	status = ice_aq_send_cmd(hw, &desc, NULL, 0, cd);
	if (!status) {
		first_cntr = LE16_TO_CPU(cmd->ops.resp.first_counter);
		last_cntr = LE16_TO_CPU(cmd->ops.resp.last_counter);
		if (first_cntr == ICE_AQC_ACL_ALLOC_CNT_INVAL ||
		    last_cntr == ICE_AQC_ACL_ALLOC_CNT_INVAL)
			return ICE_ERR_OUT_OF_RANGE;
		cntrs->first_cntr = first_cntr;
		cntrs->last_cntr = last_cntr;
	}
	return status;
}

/**
 * ice_aq_dealloc_acl_cntrs - deallocate ACL counters
 * @hw: pointer to the HW struct
 * @cntrs: ptr to buffer describing input and output params
 * @cd: pointer to command details structure or NULL
 *
 * De-allocate ACL counters (direct 0x0C17)
 */
int
ice_aq_dealloc_acl_cntrs(struct ice_hw *hw, struct ice_acl_cntrs *cntrs,
			 struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_dealloc_counters *cmd;
	struct ice_aq_desc desc;
	int status;

	/* check for invalid params */
	status = ice_aq_acl_cntrs_chk_params(cntrs);
	if (status)
		return status;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_dealloc_acl_counters);
	cmd = &desc.params.dealloc_counters;
	cmd->first_counter = CPU_TO_LE16(cntrs->first_cntr);
	cmd->last_counter = CPU_TO_LE16(cntrs->last_cntr);
	cmd->counters_type = cntrs->type;
	cmd->bank_alloc = cntrs->bank;
	return ice_aq_send_cmd(hw, &desc, NULL, 0, cd);
}

#ifdef ACL_DEBUG
/**
 * ice_aq_query_acl_cntrs - query ACL counter
 * @hw: pointer to the HW struct
 * @bank: queries counter bank
 * @index: queried counter index
 * @cntr_val: pointer to counter or packet counter value
 * @cd: pointer to command details structure or NULL
 *
 * Query ACL counter (direct 0x0C27)
 */
int
ice_aq_query_acl_cntrs(struct ice_hw *hw, u8 bank, u16 index, u64 *cntr_val,
		       struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_query_counter *cmd;
	struct ice_aq_desc desc;
	int status;

	if (!cntr_val)
		return ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_query_acl_counter);
	cmd = &desc.params.query_counter;
	cmd->counter_index = CPU_TO_LE16(index);
	cmd->counter_bank = bank;
	status = ice_aq_send_cmd(hw, &desc, NULL, 0, cd);
	if (!status) {
		__le64 resp_val = 0;

		ice_memcpy(&resp_val, cmd->ops.resp.val,
			   sizeof(cmd->ops.resp.val), ICE_NONDMA_TO_NONDMA);
		*cntr_val = LE64_TO_CPU(resp_val);
	}
	return status;
}
#endif /* ACL_DEBUG */

/**
 * ice_prog_acl_prof_ranges - program ACL profile ranges
 * @hw: pointer to the HW struct
 * @prof_id: programmed or updated profile ID
 * @buf: pointer to input buffer
 * @cd: pointer to command details structure or NULL
 *
 * Program ACL profile ranges (indirect 0x0C1E)
 */
int
ice_prog_acl_prof_ranges(struct ice_hw *hw, u8 prof_id,
			 struct ice_aqc_acl_profile_ranges *buf,
			 struct ice_sq_cd *cd)
{
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc,
				      ice_aqc_opc_program_acl_prof_ranges);
	desc.params.profile.profile_id = prof_id;
	desc.flags |= CPU_TO_LE16(ICE_AQ_FLAG_RD);
	return ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
}

/**
 * ice_query_acl_prof_ranges - query ACL profile ranges
 * @hw: pointer to the HW struct
 * @prof_id: programmed or updated profile ID
 * @buf: pointer to response buffer
 * @cd: pointer to command details structure or NULL
 *
 * Query ACL profile ranges (indirect 0x0C22)
 */
int
ice_query_acl_prof_ranges(struct ice_hw *hw, u8 prof_id,
			  struct ice_aqc_acl_profile_ranges *buf,
			  struct ice_sq_cd *cd)
{
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc,
				      ice_aqc_opc_query_acl_prof_ranges);
	desc.params.profile.profile_id = prof_id;
	return ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
}

/**
 * ice_aq_alloc_acl_scen - allocate ACL scenario
 * @hw: pointer to the HW struct
 * @scen_id: memory location to receive allocated scenario ID
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Allocate ACL scenario (indirect 0x0C14)
 */
int
ice_aq_alloc_acl_scen(struct ice_hw *hw, u16 *scen_id,
		      struct ice_aqc_acl_scen *buf, struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_alloc_scen *cmd;
	struct ice_aq_desc desc;
	int status;

	if (!scen_id)
		return ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_alloc_acl_scen);
	desc.flags |= CPU_TO_LE16(ICE_AQ_FLAG_RD);
	cmd = &desc.params.alloc_scen;

	status = ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
	if (!status)
		*scen_id = LE16_TO_CPU(cmd->ops.resp.scen_id);

	return status;
}

/**
 * ice_aq_dealloc_acl_scen - deallocate ACL scenario
 * @hw: pointer to the HW struct
 * @scen_id: scen_id to be deallocated (input and output field)
 * @cd: pointer to command details structure or NULL
 *
 * Deallocate ACL scenario (direct 0x0C15)
 */
int
ice_aq_dealloc_acl_scen(struct ice_hw *hw, u16 scen_id, struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_dealloc_scen *cmd;
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_dealloc_acl_scen);
	cmd = &desc.params.dealloc_scen;
	cmd->scen_id = CPU_TO_LE16(scen_id);

	return ice_aq_send_cmd(hw, &desc, NULL, 0, cd);
}

/**
 * ice_aq_update_query_scen - update or query ACL scenario
 * @hw: pointer to the HW struct
 * @opcode: AQ command opcode for either query or update scenario
 * @scen_id: scen_id to be updated or queried
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Calls update or query ACL scenario
 */
static int
ice_aq_update_query_scen(struct ice_hw *hw, u16 opcode, u16 scen_id,
			 struct ice_aqc_acl_scen *buf, struct ice_sq_cd *cd)
{
	struct ice_aqc_acl_update_query_scen *cmd;
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, opcode);
	if (opcode == ice_aqc_opc_update_acl_scen)
		desc.flags |= CPU_TO_LE16(ICE_AQ_FLAG_RD);
	cmd = &desc.params.update_query_scen;
	cmd->scen_id = CPU_TO_LE16(scen_id);

	return ice_aq_send_cmd(hw, &desc, buf, sizeof(*buf), cd);
}

/**
 * ice_aq_update_acl_scen - update ACL scenario
 * @hw: pointer to the HW struct
 * @scen_id: scen_id to be updated
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Update ACL scenario (indirect 0x0C1B)
 */
int
ice_aq_update_acl_scen(struct ice_hw *hw, u16 scen_id,
		       struct ice_aqc_acl_scen *buf, struct ice_sq_cd *cd)
{
	return ice_aq_update_query_scen(hw, ice_aqc_opc_update_acl_scen,
					scen_id, buf, cd);
}

/**
 * ice_aq_query_acl_scen - query ACL scenario
 * @hw: pointer to the HW struct
 * @scen_id: scen_id to be queried
 * @buf: address of indirect data buffer
 * @cd: pointer to command details structure or NULL
 *
 * Query ACL scenario (indirect 0x0C23)
 */
int
ice_aq_query_acl_scen(struct ice_hw *hw, u16 scen_id,
		      struct ice_aqc_acl_scen *buf, struct ice_sq_cd *cd)
{
	return ice_aq_update_query_scen(hw, ice_aqc_opc_query_acl_scen,
					scen_id, buf, cd);
}
#endif /* !NO_ACL_SUPPORT */
