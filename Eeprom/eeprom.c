/**
  ******************************************************************************
  * @file    EEPROM_Emulation/src/eeprom.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    10-October-2011
  * @brief   This file provides all the EEPROM emulation firmware functions.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/** @addtogroup EEPROM_Emulation
  * @{
  */ 

/* Includes ------------------------------------------------------------------*/
#include "eeprom.h"
#include "rtc.h"
//#include "ds1307_for_stm32_hal.h"
//#include "Auxiliary.hpp"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Global variable used to store variable value in read sequence */
uint16_t DataVar = 0;


/* Virtual address defined by the user: 0xFFFF value is prohibited */
//extern uint16_t VirtAddVarTab[NB_OF_VAR];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static uint16_t EE_Format(void);

static uint16_t EE_FindValidPage(uint8_t Operation);
static uint16_t EE_VerifyPageFullWriteVariable(uint16_t VirtAddress, uint16_t Data);
static uint16_t EE_PageTransfer(uint16_t VirtAddress, uint16_t Data);

/**
  * @brief  Restore the pages to a known good state in case of page's status
  *   corruption after a power loss.
  * @param  None.
  * @retval - Flash error code: on write Flash error
  *         - FLASH_COMPLETE: on success
  */
uint16_t EE_Init(void)
{
  uint16_t PageStatus0 = 6, PageStatus1 = 6;
  uint16_t VarIdx = 0;
  uint16_t EepromStatus = 0, ReadStatus = 0;
  int16_t x = -1;
  uint16_t  FlashStatus;
  HAL_StatusTypeDef HalFlashStatus;

  /* Get Page0 status */
  PageStatus0 = (*(__IO uint16_t*)PAGE0_BASE_ADDRESS);
  /* Get Page1 status */
  PageStatus1 = (*(__IO uint16_t*)PAGE1_BASE_ADDRESS);

  /* Check for invalid header states and repair if necessary */
  switch (PageStatus0)
  {
    case ERASED:
      if (PageStatus1 == VALID_PAGE) /* Page0 erased, Page1 valid */
      {
        /* Erase Page0 */
	      FLASH_Erase_Sector(PAGE0_ID, VOLTAGE_RANGE);
        /* If erase operation was failed, a Flash error code is returned */
        //if (FlashStatus != FLASH_COMPLETE)
        //{
        //  return FlashStatus;
        //}
      }
      else if (PageStatus1 == RECEIVE_DATA) /* Page0 erased, Page1 receive */
      {
        /* Erase Page0 */
	     FLASH_Erase_Sector(PAGE0_ID, VOLTAGE_RANGE);
        //FlashStatus = FLASH_EraseSector(PAGE0_ID, VOLTAGE_RANGE);
        /* If erase operation was failed, a Flash error code is returned */
        //if (FlashStatus != FLASH_COMPLETE)
        ///{
        //  return FlashStatus;
        //}
        /* Mark Page1 as valid */
	    HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, PAGE1_BASE_ADDRESS, VALID_PAGE);  
        //FlashStatus = FLASH_ProgramHalfWord(PAGE1_BASE_ADDRESS, VALID_PAGE);
        /* If program operation was failed, a Flash error code is returned */
        if (HalFlashStatus != HAL_OK)
        {
          return HalFlashStatus;
        }
      }
      else /* First EEPROM access (Page0&1 are erased) or invalid state -> format EEPROM */
      {
        /* Erase both Page0 and Page1 and set Page0 as valid page */
        FlashStatus = EE_Format();
        /* If erase/program operation was failed, a Flash error code is returned */
        if (FlashStatus != HAL_OK)
        {
          return FlashStatus;
        }
      }
      break;

    case RECEIVE_DATA:
      if (PageStatus1 == VALID_PAGE) /* Page0 receive, Page1 valid */
      {
        /* Transfer data from Page1 to Page0 */
        for (VarIdx = 0; VarIdx < NB_OF_VAR; VarIdx++)
        {
          if (( *(__IO uint16_t*)(PAGE0_BASE_ADDRESS + 6)) == VIRT_ADDR_BEGIN + VarIdx)
          {
            x = VarIdx;
          }
          if (VarIdx != x)
          {
            /* Read the last variables' updates */
	          ReadStatus = EE_ReadVariable(VIRT_ADDR_BEGIN + VarIdx, &DataVar);
            /* In case variable corresponding to the virtual address was found */
            if (ReadStatus != 0x1)
            {
              /* Transfer the variable to the Page0 */
	            EepromStatus = EE_VerifyPageFullWriteVariable(VIRT_ADDR_BEGIN + VarIdx, DataVar);
              /* If program operation was failed, a Flash error code is returned */
              if (EepromStatus != HAL_OK)
              {
                return EepromStatus;
              }
            }
          }
        }
        /* Mark Page0 as valid */
        //FlashStatus = FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, VALID_PAGE);
	    HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, PAGE0_BASE_ADDRESS, VALID_PAGE);  
        /* If program operation was failed, a Flash error code is returned */
        if (HalFlashStatus != HAL_OK)
        {
          return HalFlashStatus;
        }
        /* Erase Page1 */
	      
	    FLASH_Erase_Sector(PAGE1_ID, VOLTAGE_RANGE);  
        //FlashStatus = FLASH_EraseSector(PAGE1_ID, VOLTAGE_RANGE);
        /* If erase operation was failed, a Flash error code is returned */
        //if (FlashStatus != FLASH_COMPLETE)
        //{
        //  return FlashStatus;
        //}
      }
      else if (PageStatus1 == ERASED) /* Page0 receive, Page1 erased */
      {
        /* Erase Page1 */
	    FLASH_Erase_Sector(PAGE1_ID, VOLTAGE_RANGE);  
        //FlashStatus = FLASH_EraseSector(PAGE1_ID, VOLTAGE_RANGE);
        /* If erase operation was failed, a Flash error code is returned */
        //if (FlashStatus != FLASH_COMPLETE)
        //{
        //  return FlashStatus;
        //}
        /* Mark Page0 as valid */
	    HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, PAGE0_BASE_ADDRESS, VALID_PAGE);  
       // FlashStatus = FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, VALID_PAGE);
        /* If program operation was failed, a Flash error code is returned */
        if (HalFlashStatus != HAL_OK)
        {
          return HalFlashStatus;
        }
      }
      else /* Invalid state -> format eeprom */
      {
        /* Erase both Page0 and Page1 and set Page0 as valid page */
        FlashStatus = EE_Format();
        /* If erase/program operation was failed, a Flash error code is returned */
        if (FlashStatus != HAL_OK)
        {
          return FlashStatus;
        }
      }
      break;

    case VALID_PAGE:
      if (PageStatus1 == VALID_PAGE) /* Invalid state -> format eeprom */
      {
        /* Erase both Page0 and Page1 and set Page0 as valid page */
        FlashStatus = EE_Format();
        /* If erase/program operation was failed, a Flash error code is returned */
        if (FlashStatus != HAL_OK)
        {
          return FlashStatus;
        }
      }
      else if (PageStatus1 == ERASED) /* Page0 valid, Page1 erased */
      {
        /* Erase Page1 */
	    FLASH_Erase_Sector(PAGE1_ID, VOLTAGE_RANGE);  
        //FlashStatus = FLASH_EraseSector(PAGE1_ID, VOLTAGE_RANGE);
        /* If erase operation was failed, a Flash error code is returned */
        //if (FlashStatus != FLASH_COMPLETE)
        //{
        //  return FlashStatus;
        //}
      }
      else /* Page0 valid, Page1 receive */
      {
        /* Transfer data from Page0 to Page1 */
        for (VarIdx = 0; VarIdx < NB_OF_VAR; VarIdx++)
        {
	        if ((*(__IO uint16_t*)(PAGE1_BASE_ADDRESS + 6)) == VIRT_ADDR_BEGIN + VarIdx)
          {
            x = VarIdx;
          }
          if (VarIdx != x)
          {
            /* Read the last variables' updates */
	          ReadStatus = EE_ReadVariable(VIRT_ADDR_BEGIN + VarIdx, &DataVar);
            /* In case variable corresponding to the virtual address was found */
            if (ReadStatus != 0x1)
            {
              /* Transfer the variable to the Page1 */
	            EepromStatus = EE_VerifyPageFullWriteVariable(VIRT_ADDR_BEGIN + VarIdx, DataVar);
              /* If program operation was failed, a Flash error code is returned */
              if (EepromStatus != HAL_OK)
              {
                return EepromStatus;
              }
            }
          }
        }
        /* Mark Page1 as valid */
	    HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, PAGE1_BASE_ADDRESS, VALID_PAGE);  
  
        //FlashStatus = FLASH_ProgramHalfWord(PAGE1_BASE_ADDRESS, VALID_PAGE);
        /* If program operation was failed, a Flash error code is returned */
        if (HalFlashStatus != HAL_OK)
        {
          return HalFlashStatus;
        }
        /* Erase Page0 */
	    FLASH_Erase_Sector(PAGE1_ID, VOLTAGE_RANGE);  
        //FlashStatus = FLASH_EraseSector(PAGE0_ID, VOLTAGE_RANGE);
        /* If erase operation was failed, a Flash error code is returned */
        //if (FlashStatus != FLASH_COMPLETE)
        //{
        //  return FlashStatus;
        //}
      }
      break;

    default:  /* Any other state -> format eeprom */
      /* Erase both Page0 and Page1 and set Page0 as valid page */
      FlashStatus = EE_Format();
      /* If erase/program operation was failed, a Flash error code is returned */
      if (FlashStatus != HAL_OK)
      {
        return FlashStatus;
      }
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Returns the last stored variable data, if found, which correspond to
  *   the passed virtual address
  * @param  VirtAddress: Variable virtual address
  * @param  Data: Global variable contains the read variable value
  * @retval Success or error status:
  *           - 0: if variable was found
  *           - 1: if the variable was not found
  *           - NO_VALID_PAGE: if no valid page was found.
  */
uint16_t EE_ReadVariable(uint16_t VirtAddress, uint16_t* Data)
{
  uint16_t ValidPage = PAGE0;
  uint16_t AddressValue = 0x5555, ReadStatus = 1;
  uint32_t Address = EEPROM_START_ADDRESS, PageStartAddress = EEPROM_START_ADDRESS;

  /* Get active Page for read operation */
  ValidPage = EE_FindValidPage(READ_FROM_VALID_PAGE);

  /* Check if there is no valid page */
  if (ValidPage == NO_VALID_PAGE)
  {
    return  NO_VALID_PAGE;
  }

  /* Get the valid Page start Address */
  PageStartAddress = (uint32_t)(EEPROM_START_ADDRESS + (uint32_t)(ValidPage * PAGE_SIZE));

  /* Get the valid Page end Address */
  Address = (uint32_t)((EEPROM_START_ADDRESS - 2) + (uint32_t)((1 + ValidPage) * PAGE_SIZE));

  /* Check each active page address starting from end */
  while (Address > (PageStartAddress + 2))
  {
    /* Get the current location content to be compared with virtual address */
    AddressValue = (*(__IO uint16_t*)Address);

    /* Compare the read address with the virtual address */
    if (AddressValue == VirtAddress)
    {
      /* Get content of Address-2 which is variable value */
      *Data = (*(__IO uint16_t*)(Address - 2));

      /* In case variable value is read, reset ReadStatus flag */
      ReadStatus = 0;

      break;
    }
    else
    {
      /* Next address location */
      Address = Address - 4;
    }
  }

  /* Return ReadStatus value: (0: variable exist, 1: variable doesn't exist) */
  return ReadStatus;
}

/**
  * @brief  Writes/upadtes variable data in EEPROM.
  * @param  VirtAddress: Variable virtual address
  * @param  Data: 16 bit data to be written
  * @retval Success or error status:
  *           - FLASH_COMPLETE: on success
  *           - PAGE_FULL: if valid page is full
  *           - NO_VALID_PAGE: if no valid page was found
  *           - Flash error code: on write Flash error
  */
uint16_t EE_WriteVariable(uint16_t VirtAddress, uint16_t Data)
{
  uint16_t Status = 0;
/* Write the variable virtual address and value in the EEPROM */
  Status = EE_VerifyPageFullWriteVariable(VirtAddress, Data);

  /* In case the EEPROM active page is full */
  if (Status == PAGE_FULL)
  {
    /* Perform Page transfer */
	  Status = EE_PageTransfer(VirtAddress, Data);
  }

  /* Return last operation status */
  return Status;
}

/**
  * @brief  Erases PAGE and PAGE1 and writes VALID_PAGE header to PAGE
  * @param  None
  * @retval Status of the last operation (Flash write or erase) done during
  *         EEPROM formating
  */
static uint16_t EE_Format(void)
{
  //FLASH_Status FlashStatus = FLASH_COMPLETE;
  HAL_StatusTypeDef HalFlashStatus = HAL_OK;

  /* Erase Page0 */
  FLASH_Erase_Sector(PAGE0_ID, VOLTAGE_RANGE);

  /* If erase operation was failed, a Flash error code is returned */
  if (HalFlashStatus != HAL_OK)
  {
    return HalFlashStatus;
  }

  /* Set Page0 as valid page: Write VALID_PAGE at Page0 base address */
  HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, PAGE0_BASE_ADDRESS, VALID_PAGE);  

  //FlashStatus = FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, VALID_PAGE);

  /* If program operation was failed, a Flash error code is returned */
  if (HalFlashStatus != HAL_OK)
  {
    return HalFlashStatus;
  }

  /* Erase Page1 */
  FLASH_Erase_Sector(PAGE1_ID, VOLTAGE_RANGE);

  /* Return Page1 erase operation status */
  return HalFlashStatus;
}

/**
  * @brief  Find valid Page for write or read operation
  * @param  Operation: operation to achieve on the valid page.
  *   This parameter can be one of the following values:
  *     @arg READ_FROM_VALID_PAGE: read operation from valid page
  *     @arg WRITE_IN_VALID_PAGE: write operation from valid page
  * @retval Valid page number (PAGE or PAGE1) or NO_VALID_PAGE in case
  *   of no valid page was found
  */
static uint16_t EE_FindValidPage(uint8_t Operation)
{
  uint16_t PageStatus0 = 6, PageStatus1 = 6;

  /* Get Page0 actual status */
  PageStatus0 = (*(__IO uint16_t*)PAGE0_BASE_ADDRESS);

  /* Get Page1 actual status */
  PageStatus1 = (*(__IO uint16_t*)PAGE1_BASE_ADDRESS);

  /* Write or read operation */
  switch (Operation)
  {
    case WRITE_IN_VALID_PAGE:   /* ---- Write operation ---- */
      if (PageStatus1 == VALID_PAGE)
      {
        /* Page0 receiving data */
        if (PageStatus0 == RECEIVE_DATA)
        {
          return PAGE0;         /* Page0 valid */
        }
        else
        {
          return PAGE1;         /* Page1 valid */
        }
      }
      else if (PageStatus0 == VALID_PAGE)
      {
        /* Page1 receiving data */
        if (PageStatus1 == RECEIVE_DATA)
        {
          return PAGE1;         /* Page1 valid */
        }
        else
        {
          return PAGE0;         /* Page0 valid */
        }
      }
      else
      {
        return NO_VALID_PAGE;   /* No valid Page */
      }

    case READ_FROM_VALID_PAGE:  /* ---- Read operation ---- */
      if (PageStatus0 == VALID_PAGE)
      {
        return PAGE0;           /* Page0 valid */
      }
      else if (PageStatus1 == VALID_PAGE)
      {
        return PAGE1;           /* Page1 valid */
      }
      else
      {
        return NO_VALID_PAGE ;  /* No valid Page */
      }

    default:
      return PAGE0;             /* Page0 valid */
  }
}

/**
  * @brief  Verify if active page is full and Writes variable in EEPROM.
  * @param  VirtAddress: 16 bit virtual address of the variable
  * @param  Data: 16 bit data to be written as variable value
  * @retval Success or error status:
  *           - FLASH_COMPLETE: on success
  *           - PAGE_FULL: if valid page is full
  *           - NO_VALID_PAGE: if no valid page was found
  *           - Flash error code: on write Flash error
  */
static uint16_t EE_VerifyPageFullWriteVariable(uint16_t VirtAddress, uint16_t Data)
{
  //FLASH_Status FlashStatus = FLASH_COMPLETE;
  HAL_StatusTypeDef HalFlashStatus = HAL_OK;
	
  uint16_t ValidPage = PAGE0;
  uint32_t Address = EEPROM_START_ADDRESS, 
  PageEndAddress = EEPROM_START_ADDRESS+PAGE_SIZE;

  /* Get valid Page for write operation */
  ValidPage = EE_FindValidPage(WRITE_IN_VALID_PAGE);

  /* Check if there is no valid page */
  if (ValidPage == NO_VALID_PAGE)
  {
    return  NO_VALID_PAGE;
  }

  /* Get the valid Page start Address */
  Address = (uint32_t)(EEPROM_START_ADDRESS + (uint32_t)(ValidPage * PAGE_SIZE));

  /* Get the valid Page end Address */
  PageEndAddress = (uint32_t)((EEPROM_START_ADDRESS - 2) + (uint32_t)((1 + ValidPage) * PAGE_SIZE));

  /* Check each active page address starting from begining */
  while (Address < PageEndAddress)
  {
    /* Verify if Address and Address+2 contents are 0xFFFFFFFF */
    if ((*(__IO uint32_t*)Address) == 0xFFFFFFFF)
    {
      /* Set variable data */
	  HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address, Data);  
      //FlashStatus = FLASH_ProgramHalfWord(Address, Data);
      /* If program operation was failed, a Flash error code is returned */
      if (HalFlashStatus != HAL_OK)
      {
	      HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address, Data);  
	      if (HalFlashStatus != HAL_OK)
	      {
		      return HalFlashStatus;
	      }
      }
      /* Set variable virtual address */
	  HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address + 2, VirtAddress);  
      //FlashStatus = FLASH_ProgramHalfWord(Address + 2, VirtAddress);
      /* Return program operation status */
      return HalFlashStatus;
    }
    else
    {
      /* Next address location */
      Address = Address + 4;
    }
  }

  /* Return PAGE_FULL in case the valid page is full */
  return PAGE_FULL;
}

/**
  * @brief  Transfers last updated variables data from the full Page to
  *   an empty one.
  * @param  VirtAddress: 16 bit virtual address of the variable
  * @param  Data: 16 bit data to be written as variable value
  * @retval Success or error status:
  *           - FLASH_COMPLETE: on success
  *           - PAGE_FULL: if valid page is full
  *           - NO_VALID_PAGE: if no valid page was found
  *           - Flash error code: on write Flash error
  */
static uint16_t EE_PageTransfer(uint16_t VirtAddress, uint16_t Data)
{
  //FLASH_Status FlashStatus = FLASH_COMPLETE;
  HAL_StatusTypeDef HalFlashStatus = HAL_OK;
  HAL_StatusTypeDef EepromStatus = HAL_OK;
  HAL_StatusTypeDef ReadStatus = HAL_OK;
	
  uint32_t NewPageAddress = EEPROM_START_ADDRESS;
  uint16_t OldPageId=0;
  uint16_t ValidPage = PAGE0, VarIdx = 0;
  //uint16_t EepromStatus = 0, ReadStatus = 0;

  /* Get active Page for read operation */
  ValidPage = EE_FindValidPage(READ_FROM_VALID_PAGE);

  if (ValidPage == PAGE1)       /* Page1 valid */
  {
    /* New page address where variable will be moved to */
    NewPageAddress = PAGE0_BASE_ADDRESS;

    /* Old page ID where variable will be taken from */
    OldPageId = PAGE1_ID;
  }
  else if (ValidPage == PAGE0)  /* Page0 valid */
  {
    /* New page address  where variable will be moved to */
    NewPageAddress = PAGE1_BASE_ADDRESS;

    /* Old page ID where variable will be taken from */
    OldPageId = PAGE0_ID;
  }
  else
  {
    return NO_VALID_PAGE;       /* No valid Page */
  }

  /* Set the new Page status to RECEIVE_DATA status */
  HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, NewPageAddress, RECEIVE_DATA);  
  //FlashStatus = FLASH_ProgramHalfWord(NewPageAddress, RECEIVE_DATA);
  /* If program operation was failed, a Flash error code is returned */
  if (HalFlashStatus != HAL_OK)
  {
    return HalFlashStatus;
  }

  /* Write the variable passed as parameter in the new active page */
  EepromStatus = EE_VerifyPageFullWriteVariable(VirtAddress, Data);
  /* If program operation was failed, a Flash error code is returned */
  if (EepromStatus != HAL_OK)
  {
    return EepromStatus;
  }

  /* Transfer process: transfer variables from old to the new active page */
  for (VarIdx = 0; VarIdx < NB_OF_VAR; VarIdx++)
  {
	  if (VIRT_ADDR_BEGIN + VarIdx != VirtAddress)  /* Check each variable except the one passed as parameter */
    {
      /* Read the other last variable updates */
	    ReadStatus = EE_ReadVariable(VIRT_ADDR_BEGIN + VarIdx, &DataVar);
      /* In case variable corresponding to the virtual address was found */
      if (ReadStatus != 0x1)
      {
        /* Transfer the variable to the new active page */
	      EepromStatus = EE_VerifyPageFullWriteVariable(VIRT_ADDR_BEGIN + VarIdx, DataVar);
        /* If program operation was failed, a Flash error code is returned */
        if (EepromStatus != HAL_OK)
        {
          return EepromStatus;
        }
      }
    }
  }

  /* Erase the old Page: Set old Page status to ERASED status */
  FLASH_Erase_Sector(OldPageId, VOLTAGE_RANGE);
  /* If erase operation was failed, a Flash error code is returned */
  if (HalFlashStatus != HAL_OK)
  {
    return HalFlashStatus;
  }

  /* Set new Page status to VALID_PAGE status */
  HalFlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, NewPageAddress, VALID_PAGE);  
  //FlashStatus = FLASH_ProgramHalfWord(NewPageAddress, VALID_PAGE);
  /* If program operation was failed, a Flash error code is returned */
  if (HalFlashStatus != HAL_OK)
  {
    return HalFlashStatus;
  }

  /* Return last operation flash status */
  return HalFlashStatus;
}

uint16_t EE_Write_Array(uint16_t initVirtAddr, uint16_t* data, uint8_t size)
{
	uint16_t FlashStatus;
	for (uint8_t i = 0; i < size; i++)
	{
		uint16_t value = data[i];
		uint16_t address = initVirtAddr + i;
		uint16_t readData;
		uint16_t readStatus = EE_ReadVariable(address, &readData);
		if (readData != data[i])
		{
			FlashStatus = EE_WriteVariable(address, data[i]);
			readStatus = EE_ReadVariable(address, &readData);
			if (FlashStatus != HAL_OK)
			{
				return FlashStatus;
			}
		}
	}
	return FlashStatus;
}

uint16_t EE_Read_Array(uint16_t initVirtAddr, uint16_t* data, uint8_t size)
{
	uint16_t currData = 0;
	uint16_t ReadStatus;
	
	for (uint8_t i = 0; i < size; i++)
	{
		uint16_t address = initVirtAddr + i;
		ReadStatus = EE_ReadVariable(address, &currData);
		if (ReadStatus == 0)
		{
			data[i] = currData;
		}
		else 
		{
			return ReadStatus;
		}
	}
	return ReadStatus;
}

uint16_t EE_Write_Int32(uint16_t virtAddr, uint32_t num)
{
	uint16_t FlashStatus;
	
	union
	{
		uint16_t arr[2];
		uint32_t fnum;
	}convert;
	
	convert.fnum = num;
	
	FlashStatus = EE_Write_Array(virtAddr, convert.arr, 2);
	return FlashStatus;
}

uint32_t EE_Read_Int32(uint16_t virtAddr)
{
	uint16_t ReadStatus;
	
	union
	{
		uint16_t arr[2];
		uint32_t fnum;
	}convert;
	
	ReadStatus = EE_Read_Array(virtAddr, convert.arr, 2);
	if (ReadStatus == 0)
	{
		return convert.fnum;
	}
	
	return 0;	
}

uint16_t EE_Write_Int64(uint16_t virtAddr, uint64_t num)
{
	uint16_t FlashStatus;
	
	union
	{
		uint16_t arr[4];
		uint64_t fnum;
	}convert;
	
	convert.fnum = num;
	
	FlashStatus = EE_Write_Array(virtAddr, convert.arr, 4);
	return FlashStatus;
}

uint64_t EE_Read_Int64(uint16_t virtAddr)
{
	uint16_t ReadStatus;
	
	union
	{
		uint16_t arr[4];
		uint64_t fnum;
	}convert;
	
	ReadStatus = EE_Read_Array(virtAddr, convert.arr, 4);
	if (ReadStatus == 0)
	{
		return convert.fnum;
	}
	
	return 0;	
}

uint16_t EE_Write_Float(uint16_t virtAddr, float num)
{
	uint16_t FlashStatus;
	
	union
	{
		uint16_t arr[2];
		float fnum;
	}convert;
	
	convert.fnum = num;
	
	FlashStatus = EE_Write_Array(virtAddr, convert.arr, 2);
	return FlashStatus;
}




float EE_Read_Float(uint16_t virtAddr)
{
	uint16_t ReadStatus;
	
	union
	{
		uint16_t arr[2];
		float fnum;
	}convert;
	
	ReadStatus = EE_Read_Array(virtAddr, convert.arr, 2);
	if (ReadStatus == 0)
	{
		return convert.fnum;
	}
	
	return 0;	
}

uint16_t EE_Write_Double(uint16_t virtAddr, double num)
{
	uint16_t FlashStatus;

	union
	{
		uint16_t arr[4];
		double dnum;
	}convert;
	
	convert.dnum = num;
	
	FlashStatus = EE_Write_Array(virtAddr, convert.arr, 4);
	return FlashStatus;
}

double EE_Read_Double(uint16_t virtAddr)
{
	uint16_t ReadStatus;
	
	union
	{
		uint16_t arr[4];
		double dnum;
	}convert;
	
	ReadStatus = EE_Read_Array(virtAddr, convert.arr, 4);
	if (ReadStatus == 0)
	{
		return convert.dnum;
	}
	return 0;
}


uint16_t EE_Write_CurrentDate(uint16_t virtAddr)
{
	uint16_t date[7] = { 0 };
	
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	date[0] = sDate.Year + 2000;
	date[1] = sDate.Month;
	date[2] = sDate.Date;
	date[3] = sTime.Hours;
	date[4] = sTime.Minutes;
	date[5] = sTime.Seconds;
	date[6] = sDate.WeekDay;
	
	uint16_t Status = EE_Write_Array(virtAddr, date, 7);
	return Status;
	
}


void EE_Read_Date(uint16_t virtAddr, uint16_t* date)
{
	EE_Read_Array(virtAddr, date, 7);
}

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/



