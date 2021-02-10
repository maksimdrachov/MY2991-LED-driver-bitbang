/*
 * MY9221.c
 *
 * Defines necessary functions to control a MY9221 LED driver
 *
 *  Created on: 08 Feb 2021
 *      Author: Maksim Drachov
 */

#include <stdio.h>

void CMDArray_Init(int *CMDArray, int hspd, int bs, int gck, int sep, int osc, int pol, int cntset, int onest)
{
	switch (hspd)
	{
		case 0:
			printf("MY9221: Slow mode selected");
			CMDArray[10] = 0;
			break;

		case 1:
			printf("MY9221: Fast mode selected");
			CMDArray[10] = 1;
			break;

		default:
			printf("MY9221: MODE BAD INPUT (CMDArray_Init)");
			CMDArray[10] = -1;
			break;
	}

	switch (bs)
	{
		case 0:
			printf("MY9221: 8-bit grayscale selected");
			CMDArray[8] = 0;
			CMDArray[9] = 0;
			break;

		case 1:
			printf("MY9221: 12-bit grayscale selected");
			CMDArray[8] = 1;
			CMDArray[9] = 0;
			break;

		case 2:
			printf("MY9221: 14-bit grayscale selected");
			CMDArray[8] = 0;
			CMDArray[9] = 1;
			break;

		case 3:
			printf("MY9221: 16-bit grayscale selected");
			CMDArray[8] = 1;
			CMDArray[9] = 1;
			break;

		default:
			printf("MY9221: GRAYSCALE BAD INPUT (CMDArray_Init)");
			CMDArray[8] = -1;
			CMDArray[9] = -1;
			break;
	}

	switch (gck)
	{
		case 0:
			printf("MY9221: original freq selected");
			CMDArray[5] = 0;
			CMDArray[6] = 0;
			CMDArray[7] = 0;
			break;

		case 1:
			printf("MY9221: original freq/2 selected");
			CMDArray[5] = 1;
			CMDArray[6] = 0;
			CMDArray[7] = 0;
			break;

		case 2:
			printf("MY9221: original freq/4 selected");
			CMDArray[5] = 0;
			CMDArray[6] = 1;
			CMDArray[7] = 0;
			break;

		case 3:
			printf("MY9221: original freq/8 selected");
			CMDArray[5] = 1;
			CMDArray[6] = 1;
			CMDArray[7] = 0;
			break;

		case 4:
			printf("MY9221: original freq/16 selected");
			CMDArray[5] = 0;
			CMDArray[6] = 0;
			CMDArray[7] = 1;
			break;

		case 5:
			printf("MY9221: original freq/64 selected");
			CMDArray[5] = 1;
			CMDArray[6] = 0;
			CMDArray[7] = 1;
			break;

		case 6:
			printf("MY9221: original freq/128 selected");
			CMDArray[5] = 0;
			CMDArray[6] = 1;
			CMDArray[7] = 1;
			break;

		case 7:
			printf("MY9221: original freq/256 selected");
			CMDArray[5] = 1;
			CMDArray[6] = 1;
			CMDArray[7] = 1;
			break;

		default:
			printf("MY9221: INTERNAL OSCILLATOR BAD INPUT (CMDArray_Init)");
			CMDArray[5] = 1;
			CMDArray[6] = 1;
			CMDArray[7] = 1;
			break;

	}

	switch (sep)
	{
		case 0:
			printf("MY9221: MY-PWM output waveform selected");
			CMDArray[4] = 0;
			break;

		case 1:
			printf("MY9221: APDM output waveform selected");
			CMDArray[4] = 1;
			break;

		default:
			printf("MY9221: OUTPUT WAVEFORM BAD INPUT (CMDArray_Init)");
			CMDArray[4] = -1;
			break;
	}

	switch (osc)
	{
		case 0:
			printf("MY9221: Internal oscillator selected");
			CMDArray[3] = 0;
			break;

		case 1:
			printf("MY9221: External oscillator selected");
			CMDArray[3] = 1;
			CMDArray[7] = 0;
			CMDArray[6] = 0;
			CMDArray[5] = 0;
			break;

		default:
			printf("MY9221: GRAYSCALE CLOCK BAD INPUT (CMDArray_Init)");
			CMDArray[3] = -1;
			break;
	}

	switch (pol)
	{
		case 0:
			printf("MY9221: LED driver selected");
			CMDArray[2] = 0;
			break;

		case 1:
			printf("MY9221: MY-PWM/APDM selected");
			CMDArray[2] = 1;
			break;

		default:
			printf("MY9221: OUTPUT POLARITY BAD INPUT (CMDArray_Init)");
			CMDArray[2] = -1;
			break;
	}

	switch (cntset)
	{
		case 0:
			printf("MY9221: Free running mode selected");
			CMDArray[1] = 0;
			break;

		case 1:
			if (CMDArray[3] != 1)
			{
				printf("MY9221: MODE BAD INPUT (CMDArray_Init) [osc needs to be 1!]");
				CMDArray[1] = -1;
				break;
			}
			printf("MY9221: Counter reset mode selected");
			CMDArray[1] = 1;
			break;

		default:
			printf("MY9221: MODE BAD INPUT (CMDArray_Init)");
			CMDArray[1] = -1;
			break;
	}

	switch (onest)
	{
		case 0:
			printf("MY9221: Frame cycle repeat mode selected");
			CMDArray[0] = 0;
			break;

		case 1:
			if (CMDArray[1] != 1)
			{
				printf("MY9221: CNTSET NEEDS TO BE 1! (CMDArray_Init)");
				CMDArray[0] = -1;
				break;
			}
			printf("MY9221: Frame cycle one-shot mode selected");
			CMDArray[0] = 1;
			break;

		default:
			printf("MY9221: ONE-SHOT SELECT BAD INPUT (CMDArray_Init)");
			CMDArray[0] = -1;
			break;
	}
}

void Grayscale_Init(int *GrArr, int bs, int *ClrArr)
{
	int GrayscaleBits;
	int Frame;
	int Bit;

	switch (bs)
	{
		case 0:
			printf("MY9221: 8-bit grayscale selected");
			GrayscaleBits = 8;
			break;

		case 1:
			printf("MY9221: 12-bit grayscale selected");
			GrayscaleBits = 12;
			break;

		case 2:
			printf("MY9221: 14-bit grayscale selected");
			GrayscaleBits = 14;
			break;

		case 3:
			printf("MY9221: 16-bit grayscale selected");
			GrayscaleBits = 16;
			break;

		default:
			printf("MY9221: GRAYSCALE BAD INPUT (Grayscale_Init)");
			break;
	}

	for (Frame = 11; Frame >= 0; --Frame)
	{
		for (Bit = 0; Bit < GrayscaleBits; ++Bit)
		{
			GrArr[Frame*16+Bit] = ClrArr[Bit];
		}
		for (Bit = GrayscaleBits; Bit < (16-GrayscaleBits); ++Bit)
		{
			GrArr[Frame*16+Bit] = 0;
		}

	}
}

void InputArray_Init(int *InputArray, int *CMDArray, int *GrArr)
{
	int i;

	for (i = 0; i < 192; ++i)
	{
		InputArray[i] = GrArr[i];
	}
	for (i = 192; i < 208; ++i)
	{
		InputArray[i] = CMDArray[i-192];
	}
}



