/* vim: set fileencoding=utf-8:
 *
 *                   GNU GENERAL PUBLIC LICENSE
 *                       Version 2, June 1991
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 *
 */
#ifndef CONFIG_QSPI_DMIC_REALTIME_HSI24MX2_H_B6CF7938_2243_0B65_86F1_BE8386A08CF2_INCLUDED_
#define CONFIG_QSPI_DMIC_REALTIME_HSI24MX2_H_B6CF7938_2243_0B65_86F1_BE8386A08CF2_INCLUDED_

////////////////////////////////////////////////////////////
//
//  Configuration: QSPI, AUDIO, I2S, HSI24.576M x2
//
#ifdef CONFIG_QSPI_DMIC_REALTIME_HSI24Mx2
 #define CONFIG_MODE            "QSPI+DMIC+I2SDAC+Sys49MHz"

 #define USE_HSI                    //  24.576MHz
 #define USE_OSC_CALIBRATE
 #define USE_PLL_CLOCK              //  49.152MHz
 #define PLL_N                  2   //  49.152MHz

 #if defined(USE_PLL_CLOCK) && (PLL_N != 1)
  #if PLL_N == 2
  #define USE_NPU_48M
  #elif PLL_N == 3
  #define USE_NPU_72M
  #else
   #error "not support this PLL_N"
  #endif
 #else
  #define USE_NPU_24M
 #endif

 #define USE_NPU_DIFF
 #define USE_DCCRN

 #define NOT_USE_EXTRA_MASK
// #define MASKTYPE   MASKTYPE_SQRT
// #define MASKTYPE   MASKTYPE_POWER1P5
// #define MASKTYPE   MASKTYPE_POWER2
// #define MASKTYPE   MASKTYPE_POWER3
// #define MASKTYPE   MASKTYPE_EXTRA

 #define NOT_USE_IN_MASK_SMOOTH
// #define MASKSMOOTH MASKSMOOTH_SLIDERWIN
// #define MASKSMOOTH MASKSMOOTH_GAUSS

 #define USE_SWITCH             // GPIO to select Transparency or Denoise

 #define PCM_FRAME_SIZE         160
 #define I2S_AND_AUD_SAME_FREQ
 #define USE_I2S_MASTER
 #define USE_I2S_OUT
 #define NOT_USE_I2S_IN
 #define USE_I2S_32BITS

 #define QSPI_BOOT

 // DMA_CHANNEL0 reserved for AUDIO, do not change!
 #define USE_DMIC
 #define I2STX_32BITS_ASL       13

 //#define AUDIO_CLK_PIN          GPIO_PIN_4
 //#define AUDIO_CLK_AF           GPIO_AF4_PDM0 
 //#define AUDIO_DATA_PIN         GPIO_PIN_5
 //#define AUDIO_DATA_AF          GPIO_AF5_PDM0
 #define AUDIO_CLK_PIN          GPIO_PIN_8
 #define AUDIO_CLK_AF           GPIO_AF8_PDM1
 #define AUDIO_DATA_PIN         GPIO_PIN_9
 #define AUDIO_DATA_AF          GPIO_AF9_PDM1

 #define USE_PRINTF             PRINTF_RETARGER_NONE

 #define I2STX_INSTANCE         I2S1
 #define I2STX_DMA_CHANNEL      DMA_CHANNEL1
 #define I2STX_SDO_PIN          GPIO_PIN_10
 #define I2STX_SDO_AF           GPIO_AF10_I2S1
 #define I2STX_CK_PIN           GPIO_PIN_12
 #define I2STX_CK_AF            GPIO_AF12_I2S1
 #define I2STX_WS_PIN           GPIO_PIN_13
 #define I2STX_WS_AF            GPIO_AF13_I2S1
#endif


#endif

