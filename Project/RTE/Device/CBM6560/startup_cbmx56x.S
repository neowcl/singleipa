;*******************************************************************************
;* File Name          : startup_cbmx56x.s
;* Description        : CBMX56X devices vector table for MDK-ARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the system clock
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM0 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* Author			  : ChipSea MCU Group
;* Version			  : V1.0.0
;* Date 			  : 01-11-2018.
;* copyright          : CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
;* note 
;      Licensed under MCD-CS Liberty SW License Agreement V1, (the "License");
;      You may not use this file except in compliance with the License.
;      You may obtain a copy of the License at:
;
;		  http://www.chipsea.com/software_license_agreement_liberty_v1
;
;    Unless required by applicable law or agreed to in writing, software 
;    distributed under the License is distributed on an "AS IS" BASIS, 
;    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;    See the License for the specific language governing permissions and
;    limitations under the License.
;*******************************************************************************
;
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts handler
                DCD     PVD_IRQHandler                 ; PVD detect
                DCD     WWDG_IRQHandler                ; WWDG
                DCD     TMR0_IRQHandler                ; TIM0
                DCD     TMR1_IRQHandler                ; TIM1
                DCD     0                              ; Reserved
                DCD     I2C_IRQHandler                 ; I2C
                DCD     0                              ; Reserved
                DCD     PA_IRQHandler                  ; GPIOA
                DCD     WK_IRQHandler                  ; WAKEUP
                DCD     0                              ; Reserved
                DCD     CC_IRQHandler                  ; CC
                DCD     FAULT_IRQHandler               ; SRAM PARITY FAULT
                DCD     0                              ; Reserved
                DCD     VADC_IRQHandler                ; VADC
                DCD     LN_IRQHandler                  ; LN
                DCD     SHA256_IRQHandler              ; SHA256
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler 
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  PVD_IRQHandler                 [WEAK]
                EXPORT  WWDG_IRQHandler                [WEAK]
                EXPORT  TMR0_IRQHandler                [WEAK]
                EXPORT  TMR1_IRQHandler                [WEAK]
                EXPORT  I2C_IRQHandler                 [WEAK]
                EXPORT  PA_IRQHandler                  [WEAK]
                EXPORT  WK_IRQHandler                  [WEAK]
                EXPORT  CC_IRQHandler                  [WEAK]
                EXPORT  FAULT_IRQHandler               [WEAK]
                EXPORT  VADC_IRQHandler                [WEAK]
                EXPORT  LN_IRQHandler                  [WEAK]
                EXPORT  SHA256_IRQHandler              [WEAK]
              
PVD_IRQHandler
WWDG_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
I2C_IRQHandler
PA_IRQHandler
WK_IRQHandler
CC_IRQHandler
FAULT_IRQHandler
VADC_IRQHandler
LN_IRQHandler
SHA256_IRQHandler 
                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;************END OF FILE**********

