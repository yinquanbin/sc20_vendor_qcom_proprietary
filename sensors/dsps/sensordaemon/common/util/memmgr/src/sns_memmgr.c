/*============================================================================
  @file sns_memmgr.c

  @brief
  Implements SNS memory manager interfaces.

  <br><br>

  DEPENDENCIES:  Uses BM3 memory manager.

Copyright (c) 2010-2015 Qualcomm Technologies, Inc. All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential
  ============================================================================*/

/*=====================================================================
  INCLUDES
=======================================================================*/

#include "sns_common.h"
#include "sns_memmgr.h"
#include "sns_init.h"

#include "oi_status.h"
#include "oi_support_init.h"

/*=====================================================================
  DEFINES
=======================================================================*/
#define SNS_MEMMGR_MAX_CB 1

/*=====================================================================
  STATIC VARIABLES
=======================================================================*/

static sns_memmgr_lowmem_cb_t cb_list[ SNS_MEMMGR_MAX_CB ];

/*=====================================================================
  INTERNAL FUNCTIONS
=======================================================================*/
#ifndef USE_NATIVE_MALLOC
static void
sns_memmgr_lowmem_cb( void )
{
  int i;

  for( i = 0; i < SNS_MEMMGR_MAX_CB; i++ ) {
    if( cb_list[i] != NULL ) {
      cb_list[i]();
    }
  }
}
#endif /* !USE_NATIVE_MALLOC */

/*=====================================================================
  EXTERNAL FUNCTIONS
=======================================================================*/

/*===========================================================================

  FUNCTION:   sns_memmgr_lowmem_cb_register

  ===========================================================================*/
sns_err_code_e
sns_memmgr_lowmem_cb_register( sns_memmgr_lowmem_cb_t cb, sns_heap_type heapType )
{
  UNREFERENCED_PARAMETER(heapType);
  int i;
  sns_err_code_e rv = SNS_ERR_FAILED;

  for( i = 0; i < SNS_MEMMGR_MAX_CB; i++ ) {
    if( cb_list[i] == NULL ) {
      cb_list[i] = cb;
      rv = SNS_SUCCESS;
      break;
    }
  }
  return rv;
}

/*===========================================================================

  FUNCTION:   sns_memmgr_init
  - Documented in sns_init.h
  ===========================================================================*/
sns_err_code_e
sns_memmgr_init( void )
{
#ifndef USE_NATIVE_MALLOC
  OI_STATUS err;
  int       i;

  for( i = 0; i < SNS_MEMMGR_MAX_CB; i++ ) {
    cb_list[i] = NULL;
  }

  err = OI_MEMMGR_Init( &oi_default_config_MEMMGR );

  sns_init_done();

  if( OI_OK == err ) {
    return SNS_SUCCESS;
  } else {
    return SNS_ERR_FAILED;
  }
#else
  sns_init_done();
  return SNS_SUCCESS;
#endif /* USE_NATIVE_MALLOC */
}

/*===========================================================================

  FUNCTION:   sns_memmgr_deinit
  - Documented in sns_init.h
  ===========================================================================*/
sns_err_code_e
sns_memmgr_deinit( void )
{
#ifndef USE_NATIVE_MALLOC
  OI_STATUS err;

  err = OI_MEMMGR_DeInit( );
#else
    //todo, find any/all memory used via native calls ?!?
#endif
    return SNS_SUCCESS;
}
