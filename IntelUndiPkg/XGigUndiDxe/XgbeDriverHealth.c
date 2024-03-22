/**************************************************************************

Copyright (c) 2020 - 2023, Intel Corporation. All rights reserved.

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
#include "Xgbe.h"

#define MSG_INFO_ROLLBACK_MODE                                  \
  "Firmware rollback mode detected. "                           \
  "Current version is NVM:%x.%02x 0x%08x %d.%d.%d, FW:%d.%d. "  \
  "Device may exhibit limited functionality. "                  \
  "Refer to the Intel(R) Ethernet Adapters and Devices User Guide for details on firmware rollback mode."

CHAR8  mRollbackMsg[MAX_DRIVER_HEALTH_ERROR_STRING] = {'\0'}; // placeholder, will be created at runtime

typedef enum {
  ERR_FW_RECOVERY_MODE = 0,
  ERR_FW_ROLLBACK_MODE,
  ERR_XCEIVER_MODULE_UNQUALIFIED,
  ERR_END
} DRIVER_HEALTH_ERR_INDEX;

HEALTH_MSG_ENTRY mDriverHealthEntry[] = {
  /* HII string ID,                           Message */
  {STRING_TOKEN (STR_FW_HEALTH_MESSAGE),      "Firmware recovery mode detected. Initialization failed."},
  {STRING_TOKEN (STR_FW_ROLLBACK_MESSAGE),    mRollbackMsg},
  {STRING_TOKEN (STR_XCEIVER_HEALTH_MESSAGE), "Rx/Tx is disabled on this device because an unsupported SFP+ module type was detected. Refer to the Intel(R) Network Adapters and Devices User Guide for a list of supported modules."}
};


/** Checks if FW is in operable state.

   @param[in]   UndiPrivateData  Driver private data structure
   @param[out]  ErrIdx           Index of FW error in global health error array. Valid only when
                                 return value is FALSE

   @retval   TRUE   FW is compatible & operable
   @retval   FALSE  FW is not operable
**/
BOOLEAN
IsFirmwareCompatible (
  IN   UNDI_PRIVATE_DATA        *UndiPrivateData,
  OUT  DRIVER_HEALTH_ERR_INDEX  *ErrIdx
  )
{
  if (ixgbe_fw_recovery_mode (&UndiPrivateData->NicInfo.Hw)) {
    *ErrIdx = ERR_FW_RECOVERY_MODE;
    return FALSE;
  }

  return TRUE;
}


/** Retrieves adapter specific health status information from SW/FW/HW.

   @param[in]   UndiPrivateData   Driver private data structure
   @param[out]  ErrorCount        On return, number of errors found, if any
   @param[out]  ErrorIndexes      On return, array that holds found health error indexes (from global array).
                                  Valid only when ErrorCount != 0. Must be allocated by caller

   @retval  EFI_SUCCESS            Adapter health information retrieved successfully
**/
EFI_STATUS
GetAdapterHealthStatus (
  IN   UNDI_PRIVATE_DATA  *UndiPrivateData,
  OUT  UINT16             *ErrorCount,
  OUT  UINT16             *ErrorIndexes
  )
{
  DRIVER_DATA              *AdapterInfo;
  struct ixgbe_hw          *Hw;
  DRIVER_HEALTH_ERR_INDEX  ErrIdx;

  ASSERT (UndiPrivateData != NULL);
  ASSERT (ErrorCount != NULL);

  AdapterInfo = &UndiPrivateData->NicInfo;
  Hw          = &AdapterInfo->Hw;
  ErrIdx      = ERR_END;

  *ErrorCount = 0;

  if (!IsFirmwareCompatible (UndiPrivateData, &ErrIdx)) {
    DEBUGPRINT (HEALTH, ("Improper FW state/version, err idx: %d\n", ErrIdx));
    AddHealthError (ErrorCount, ErrorIndexes, ErrIdx);
  }

  // Check module qualification & rollback only when FW is in good state
  if (ErrIdx != ERR_FW_RECOVERY_MODE) {

    if ((Hw->phy.media_type == ixgbe_media_type_fiber) ||
        (Hw->phy.media_type == ixgbe_media_type_fiber_qsfp))
    {
      AdapterInfo->XceiverModuleQualified = GetModuleQualificationResult (AdapterInfo);
      if (!AdapterInfo->XceiverModuleQualified) {
        DEBUGPRINT (HEALTH, ("Transceiver module not qualified\n"));
        AddHealthError (ErrorCount, ErrorIndexes, ERR_XCEIVER_MODULE_UNQUALIFIED);
      }
    }
  }

  return EFI_SUCCESS;
}
