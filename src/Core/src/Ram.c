#include "Ram.h"
#include <ic_config.h>
#include "modules_fmc.h"
//#include "flash.h"
//const uint32_t Record_BlockA_REVS[4] __attribute__((used)) __attribute__((section(".ARM.__at_0x0000E800"))) = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};
//const uint32_t Record_BlockB_REVS[4] __attribute__((used)) __attribute__((section(".ARM.__at_0x0000EA00"))) = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};
 _DF sdf ;//__attribute__((used)) __attribute__((section(".ARM.__at_0x0000E810")))={0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF};

//_DF	sdf ;
uint16_t adfflg;	
uint8_t	ReadRecord[DFSIZE];

static    uint8_t   *apdfadr;
static    uint8_t   adfidx;	
static void DFW_Index(void);
static void DFR_Index(void);

void DF_Erase_A(void)
{
    fmc_page_erase(116);
}

void DF_Erase_B(void)
{
    fmc_page_erase(117);
}


void DFW_Index(void)
{
    uint16_t  aidxA, aidxB;
    apdfadr = (uint8_t*)DF_FLASH_BLOCK_A;				// Search BlockA
	for( aidxA = 0; aidxA < DF_BLOCK && apdfadr[aidxA] != 0xFF; aidxA++ );

	apdfadr = (uint8_t*)DF_FLASH_BLOCK_B;				// Search BlockB
	for( aidxB = 0; aidxB < DF_BLOCK && apdfadr[aidxB] != 0xFF; aidxB++ );

    if( aidxB == 0 )							// Block B is empty ?
	{
		if( aidxA >= DF_BLOCK )					// Block A is full ?
		{
			apdfadr = (uint8_t*)DF_FLASH_BLOCK_B;		// Use BlockB
			adfidx = 0;
		} 
		else 
		{								// Block A is not full
			apdfadr = (uint8_t*)DF_FLASH_BLOCK_A;		// Use BlockA
			adfidx = aidxA;
		}
	}
    else
    {
        if( aidxA == 0 )						// Block A is empty ?
		{
			if( aidxB >= DF_BLOCK )				// Block B is full ?
			{
				apdfadr = (uint8_t*)DF_FLASH_BLOCK_A;	// Use BlockA
				adfidx = 0;
			} 
			else 
			{							// Block B is not full
				apdfadr = (uint8_t*)DF_FLASH_BLOCK_B;	// Use BlockB
				adfidx = aidxB;
			}
		} 
		else
        {
            if( aidxA < aidxB )					// Number of A less than B ?
			{
				apdfadr = (uint8_t*)DF_FLASH_BLOCK_A;	// Use BlockA
				adfidx = aidxA;
				if( aidxA >= (DF_BLOCK - 1) )	// Block A is last 3 area ?
				{
                    f_df_breq = ON;		// Set BlockB erase request
                    if( tdferase_cnt != 0xFFFF )
                    {
                        tdferase_cnt++;		// Increment DF erase times
                    }
				}
			} 
			else 
            {
                apdfadr = (uint8_t*)DF_FLASH_BLOCK_B;	// Use BlockB
                if( aidxB == DF_BLOCK )			// Block B is full ?
                {								// (It means some error.)
                    // Erase Block B
                    DF_Erase_B();
                    adfidx = 0;				// Index is first.
                } 
                else 
                {
                    adfidx = aidxB;
                    if( aidxB >= (DF_BLOCK - 1) )// Block B is last 3 area ?
                    {
                        f_df_areq = ON;	// Set BlockA erase request
                        if( tdferase_cnt != 0xFFFF )
                        {
                            tdferase_cnt++;		// Increment DF erase times
                        }
                    }
                }
            }
        }
    } 
}

uint8_t DF_Write(void)
{
    uint8_t	al1;
	uint8_t	*apwork1, *apwork2;

    DFW_Index();

    if( adfidx >= DF_BLOCK )						// Index Abnormal?
	{
		return FALSE;							// Abort
	}

    apwork1 = (uint8_t*)(apdfadr + DF_ST_OFF + ((uint16_t)adfidx * DF_LEN));

	apwork2 = apwork1;

    for( al1=0; al1 < DFSIZE; al1++ )				// Write area empty check
	{
		if( *apwork1 != 0xFF )					// Not empty ?
		{
			DF_IndexW(AREA_NG);					// Write index(area NG)
			return FALSE;						// Abort
		}
		apwork1++;								// To next data
	}

    fmc_write_flash((uint32_t)apwork2-FMC_DATA_FLASH_BASE_ADDR, adfdat, DFSIZE );

	DF_IndexW(W_OK);						// Write index(Write OK)
	
    if( f_df_breq == ON )						// BlockB Erase request exist ?
	{
		DF_Erase_B();							// BlockB erase
		f_df_breq = OFF;						// Clear BlockB erase request
	} 
	else 
	{
		if( f_df_areq == ON )					// BlockA Erase request exist ?
		{
			DF_Erase_A();						// BlockA erase
			f_df_areq = OFF;					// Clear BlockA erase request
		}
	}
	return TRUE;
}


void DF_Read(void)
{
	uint16_t	al1;
	DFR_Index();		
							// Search read area
	if( apdfadr != (uint8_t*)0xFFFF )				// DataFlash is not empty ?
	{
												// Data read loop
		for( al1=0; al1<DFSIZE; al1++,apdfadr++ )
		{
			adfdat[al1] = *apdfadr;
			ReadRecord[al1] = *apdfadr;
		}
	} 
	else 
	{									// DataFlash is empty
		for( al1=0; al1<DFSIZE; al1++ )			// Set default data
		{
			adfdat[al1] = 0;
			ReadRecord[al1] = 0;
		}
	}
}

void DFR_Index(void)
{
	uint8_t	aidx1=0xFF,aidx2=0xFF;
	uint8_t	aidx_w;

	apdfadr = (uint8_t*)DF_FLASH_BLOCK_B;				// Search from BlockB
	if( *apdfadr == 0xFF )						// BlockB is not used ?
	{
		apdfadr = (uint8_t*)DF_FLASH_BLOCK_A;			// Search BlockA
		if( *apdfadr != 0xFF )					// BlockA is used ?
		{
												// Search blank index
			for( aidx_w=0; aidx_w < DF_BLOCK && *apdfadr!=0xFF; aidx_w++,apdfadr++ )
			{
				if( *apdfadr == W_OK )			// Valid data ?
				{
					aidx1 = aidx_w;				// Set as DFindex
				}
			}

			if( aidx1 == 0xFF )					// Not exist valid data ?
			{
				apdfadr = (uint8_t*)0xFFFF;		// Set address to 0xFFFF
			} 
			else 
			{							// Valid data exist
												// Calculate data address
				apdfadr = (uint8_t*)(DF_FLASH_BLOCK_A + DF_ST_OFF + ((uint16_t)aidx1 * DF_LEN));
			}
		} 
		else 
		{								// BlockA also not used
			apdfadr = (uint8_t*)0xFFFF;			// Set address to 0xFFFF
		}
	} 
	else 
	{									// BlockB is used
												// Search blank index
		for( aidx_w=0; aidx_w < DF_BLOCK && *apdfadr!=0xFF; aidx_w++,apdfadr++ )
		{
			if( *apdfadr == W_OK )				// Valid data ?
			{
				aidx2 = aidx_w;					// Set as DFindex
			}
		}
		if( *(uint8_t*)DF_FLASH_BLOCK_A == 0xFF )		// BlockA is not used ?
		{
			if( aidx2 == 0xFF )					// Not exist valid data ?
			{
				apdfadr = (uint8_t*)0xFFFF;		// Set address to 0xFFFF
			} 
			else 
			{							// Exist valid data
				apdfadr = (uint8_t*)(DF_FLASH_BLOCK_B + DF_ST_OFF + ((uint16_t)aidx2 * DF_LEN));
			}
		} 
		else 
		{								// BlockA also used
			apdfadr = (uint8_t*)DF_FLASH_BLOCK_A;		// also Search BlockA
			for( aidx_w=0; aidx_w < DF_BLOCK && *apdfadr!=0xFF; aidx_w++,apdfadr++ )
			{
				if( *apdfadr == W_OK )			// Valid data ?
				{
					aidx1 = aidx_w;				// Tentative save as DFindex
				}
			}
			if( aidx2 == 0xFF )					// Not exist valid data on BlockB ?
			{
				if( aidx1 == 0xFF )				// BlockA also not exist ?
				{
					apdfadr = (uint8_t*)0xFFFF;	// Set address to 0xFFFF
				} 
				else 
				{						// BlockA has valid data
												// Calc data address by BlockA
					apdfadr = (uint8_t*)(DF_FLASH_BLOCK_A + DF_ST_OFF + ((uint16_t)aidx1 * DF_LEN));
				}
			} 
			else 
			{							// BlockB is valid
				if( aidx1 == 0xFF )				// Not exist valid data on BlockA ?
				{
												// Calc data address by BlockB
					apdfadr = (uint8_t*)(DF_FLASH_BLOCK_B + DF_ST_OFF + ((uint16_t)aidx2 * DF_LEN));
				} 
				else 
				{						// Both block are valid
					if( aidx1 < aidx2 )			// BlockA is less than B ?
					{
												// Use BlockA
						apdfadr = (uint8_t*)(DF_FLASH_BLOCK_A + DF_ST_OFF + ((uint16_t)aidx1 * DF_LEN));
					} 
					else 
					{					// Same or B is less than A
												// Use BlockB
						apdfadr = (uint8_t*)(DF_FLASH_BLOCK_B + DF_ST_OFF + ((uint16_t)aidx2 * DF_LEN));
					}
				}
			}
		}
	}
}

void DF_IndexW(uint8_t adata)
{
    if( apdfadr[adfidx] == 0xFF )
	{
		fmc_write_flash( (uint32_t)&apdfadr[adfidx]-FMC_DATA_FLASH_BASE_ADDR, &adata, 1);
	}
}
