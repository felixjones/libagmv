/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023-2024 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_imgp_lightmap.h
*   Date: 12/10/2023
*   Version: 0.2b
*   Updated: 1/19/2024
*   Author: Ryandracus Chapman
*
********************************************/

#include <agidl_imgp_lightmap.h>

#include <stdlib.h>

#include <agidl_cc_core.h>
#include <agidl_imgp_scale.h>
#include <agidl_img_types.h>
#include <agidl_math_utils.h>

void AGIDL_BindLightmapAndImg(void* data, void* lightdata, const u16 width, const u16 height, u16 widthl, u16 heightl, const AGIDL_CLR_FMT imgfmt, const AGIDL_CLR_FMT lightfmt, const AGIDL_LIGHT light, const COLOR blend){
	if((AGIDL_GetBitCount(imgfmt) == 24 && AGIDL_GetBitCount(lightfmt) == 24) || (AGIDL_GetBitCount(imgfmt) == 32 && AGIDL_GetBitCount(lightfmt) == 32)){
		COLOR* clrdata = data;
		const COLOR* lightclr = lightdata;

		if(width != widthl && height == heightl){
			lightclr = (COLOR*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,width/widthl,1,lightfmt);
		}
		else if(width == widthl && height != heightl){
			lightclr = (COLOR*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,1,height/heightl,lightfmt);
		}
		else if(width != widthl && height != heightl){
			lightclr = (COLOR*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,width/widthl,height/heightl,lightfmt);
		}

		for(int y = 0; y < height; y++){
			for(int x = 0; x < width; x++){
				const COLOR clrlum = AGIDL_GetClr(lightclr,x,y,width,height);
				COLOR clr = AGIDL_GetClr(clrdata,x,y,width,height);

				const u8 avg = (AGIDL_GetR(clrlum,lightfmt)+AGIDL_GetG(clrlum,lightfmt)+AGIDL_GetB(clrlum,lightfmt))/3.0f;
				const float factor = (avg / 255.0f);
				const float invfactor = 1.0f - factor;
				if(light != INVLIGHTMAP){
					clr = AGIDL_BlendColor(clr,blend,invfactor,CC_BLEND_CLR_SRCINV,imgfmt);
					AGIDL_SetClr(clrdata,clr,x,y,width,height);
				}
				else{
					clr = AGIDL_BlendColor(clr,blend,factor,CC_BLEND_CLR_SRCINV,imgfmt);
					AGIDL_SetClr(clrdata,clr,x,y,width,height);
				}
			}
		}
	}
	else if(AGIDL_GetBitCount(imgfmt) == 16 && AGIDL_GetBitCount(lightfmt) == 16){
		COLOR16* clrdata = data;
		const COLOR16* lightclr = lightdata;

		if(width != widthl && height == heightl){
			lightclr = (COLOR16*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,width/widthl,1,lightfmt);
		}
		else if(width == widthl && height != heightl){
			lightclr = (COLOR16*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,1,height/heightl,lightfmt);
		}
		else if(width != widthl && height != heightl){
			lightclr = (COLOR16*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,width/widthl,height/heightl,lightfmt);
		}

		for(int y = 0; y < height; y++){
			for(int x = 0; x < width; x++){
				const COLOR16 clrlum = AGIDL_GetClr16(lightclr,x,y,width,height);
				COLOR16 clr = AGIDL_GetClr16(clrdata,x,y,width,height);

				const u8 avg = (AGIDL_GetR(clrlum,lightfmt)+AGIDL_GetG(clrlum,lightfmt)+AGIDL_GetB(clrlum,lightfmt))/3.0f;
				const float factor = (avg / 31.0f);
				const float invfactor = 1.0f - factor;
				if(light != INVLIGHTMAP){
					clr = AGIDL_BlendColor(clr,blend,invfactor,CC_BLEND_CLR_SRCINV,imgfmt);
					AGIDL_SetClr16(clrdata,clr,x,y,width,height);
				}
				else{
					clr = AGIDL_BlendColor(clr,blend,factor,CC_BLEND_CLR_SRCINV,imgfmt);
					AGIDL_SetClr16(clrdata,clr,x,y,width,height);
				}
			}
		}
	}
	else if((AGIDL_GetBitCount(imgfmt) == 24 || AGIDL_GetBitCount(imgfmt) == 32) && AGIDL_GetBitCount(lightfmt) == 16){
		COLOR* clrdata = data;
		const COLOR16* lightclr = lightdata;

		if(width != widthl && height == heightl){
			lightclr = (COLOR16*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,width/widthl,1,lightfmt);
		}
		else if(width == widthl && height != heightl){
			lightclr = (COLOR16*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,1,height/heightl,lightfmt);
		}
		else if(width != widthl && height != heightl){
			lightclr = (COLOR16*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,width/widthl,height/heightl,lightfmt);
		}

		for(int y = 0; y < height; y++){
			for(int x = 0; x < width; x++){
				const COLOR16 clrlum = AGIDL_GetClr16(lightclr,x,y,width,height);
				COLOR clr = AGIDL_GetClr(clrdata,x,y,width,height);

				const u8 avg = (AGIDL_GetR(clrlum,lightfmt)+AGIDL_GetG(clrlum,lightfmt)+AGIDL_GetB(clrlum,lightfmt))/3.0f;
				const float factor = (avg / 31.0f);
				const float invfactor = 1.0f - factor;
				if(light != INVLIGHTMAP){
					clr = AGIDL_BlendColor(clr,blend,invfactor,CC_BLEND_CLR_SRCINV,imgfmt);
					AGIDL_SetClr(clrdata,clr,x,y,width,height);
				}
				else{
					clr = AGIDL_BlendColor(clr,blend,factor,CC_BLEND_CLR_SRCINV,imgfmt);
					AGIDL_SetClr(clrdata,clr,x,y,width,height);
				}
			}
		}
	}
	else if((AGIDL_GetBitCount(lightfmt) == 24 || AGIDL_GetBitCount(lightfmt) == 32) && AGIDL_GetBitCount(imgfmt) == 16){
		COLOR16* clrdata = data;
		const COLOR* lightclr = lightdata;

		if(width != widthl && height == heightl){
			lightclr = (COLOR*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,width/widthl,1,lightfmt);
		}
		else if(width == widthl && height != heightl){
			lightclr = (COLOR*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,1,height/heightl,lightfmt);
		}
		else if(width != widthl && height != heightl){
			lightclr = (COLOR*)AGIDL_ScaleImgDataNearest(lightdata,&widthl,&heightl,width/widthl,height/heightl,lightfmt);
		}

		for(int y = 0; y < height; y++){
			for(int x = 0; x < width; x++){
				const COLOR clrlum = AGIDL_GetClr(lightclr,x,y,width,height);
				COLOR16 clr = AGIDL_GetClr16(clrdata,x,y,width,height);

				const u8 avg = (AGIDL_GetR(clrlum,lightfmt)+AGIDL_GetG(clrlum,lightfmt)+AGIDL_GetB(clrlum,lightfmt))/3.0f;
				const float factor = (avg / 255.0f);
				const float invfactor = 1.0f - factor;
				if(light != INVLIGHTMAP){
					clr = AGIDL_BlendColor(clr,blend,invfactor,CC_BLEND_CLR_SRCINV,imgfmt);
					AGIDL_SetClr16(clrdata,clr,x,y,width,height);
				}
				else{
					clr = AGIDL_BlendColor(clr,blend,factor,CC_BLEND_CLR_SRCINV,imgfmt);
					AGIDL_SetClr16(clrdata,clr,x,y,width,height);
				}
			}
		}
	}
}

AGIDL_Point AGIDL_CreateLightPoint(const u16 x, const u16 y, const u8 size, const float bias, const int inv, const AGIDL_LIGHT_DIR dir, const COLOR clr){
	const AGIDL_Point p = {x, y, size, AGIDL_Clampf(0,bias,1.0f), AGIDL_Clamp(0,inv,1), dir, clr};
	return p;
}

void AGIDL_SetLight(AGIDL_LIGHTMAP* lightmap, const AGIDL_LIGHT light){
	lightmap->light = light;
}

void AGIDL_SetWidth(AGIDL_LIGHTMAP* lightmap, const u16 width){
	lightmap->width = width;
}

void AGIDL_SetHeight(AGIDL_LIGHTMAP* lightmap, const u16 height){
	lightmap->height = height;
}

void AGIDL_SetClrFmt(AGIDL_LIGHTMAP* lightmap, const AGIDL_CLR_FMT fmt){
	lightmap->fmt = fmt;
}

void AGIDL_InitLightmap(AGIDL_LIGHTMAP* lightmap, const AGIDL_LIGHT light, const u16 width, const u16 height, const AGIDL_CLR_FMT fmt){
	AGIDL_SetLight(lightmap,light);
	AGIDL_SetWidth(lightmap,width);
	AGIDL_SetHeight(lightmap,height);
	AGIDL_SetClrFmt(lightmap,fmt);
	lightmap->num_of_points = 0;
}

void AGIDL_AddLightPoint(AGIDL_LIGHTMAP* lightmap, const AGIDL_Point point){
	lightmap->points[lightmap->num_of_points] = point;
	lightmap->num_of_points++;
}

void AGIDL_FillLightRect(COLOR* clrs, const u16 x, const u16 y, const u16 width, const u16 height, const u8 size, const COLOR clr){
	for(u16 j = y; j < y + size; j++){
		for(u16 i = x; i < x + size; i++){
			AGIDL_SetClr(clrs,clr,i,j,width,height);
		}
	}
}

void AGIDL_FillLightRect16(COLOR16* clrs, const u16 x, const u16 y, const u16 width, const u16 height, const u8 size, const COLOR16 clr){
	for(u16 j = y; j < y + size; j++){
		for(u16 i = x; i < x + size; i++){
			AGIDL_SetClr16(clrs,clr,i,j,width,height);
		}
	}
}

int IsInXRange(const float bias, const u16 x, const u8 size, const u16 width){
	const u32 max_width_span = bias * width;

	if((x + size) >= max_width_span){
		return 0;
	}
	return 1;
}

int IsInYRange(const float bias, const u16 y, const u8 size, const u16 height){
	const u32 max_height_span = bias * height;

	if((y + size) >= max_height_span){
		return 0;
	}
	return 1;
}

int IsInInvXRange(const float bias, const u16 x, const u8 size, const u16 width){
	const u32 max_width_span = (bias * width);

	if((x - size) >= max_width_span){
		return 1;
	}
	if((x - size) <= 0){
		return 0;
	}
	return 0;
}

int IsInInvYRange(const float bias, const u16 y, const u8 size, const u16 height){
	const u32 max_height_span = bias * height;

	if((y - size) <= 0){
		return 0;
	}
	if((y - size) >= max_height_span){
		return 1;
	}
	return 0;
}

void AGIDL_FloodLightRectNE(COLOR* clrs, const COLOR clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInXRange(bias,x,size,width) && IsInYRange(bias,y,size,height)){
		AGIDL_FillLightRect(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodLightRectNE(clrs,clr,clrfactor-0.04,fmt,x+size,y,width,height,bias,size);
		AGIDL_FloodLightRectNE(clrs,clr,clrfactor-0.08,fmt,x,y+size,width,height,bias,size);
	}
}

void AGIDL_FloodLightRectSE(COLOR* clrs, const COLOR clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInInvXRange(bias,x,size,width) && IsInInvYRange(bias,y,size,height)){
		AGIDL_FillLightRect(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodLightRectSE(clrs,clr,clrfactor-0.04,fmt,x-size,y,width,height,bias,size);
		AGIDL_FloodLightRectSE(clrs,clr,clrfactor-0.08,fmt,x,y-size,width,height,bias,size);
	}
}

void AGIDL_FloodLightRectNWTOSE(COLOR* clrs, const COLOR clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInXRange(bias,x,size,width) && IsInInvYRange(bias,y,size,height)){
		AGIDL_FillLightRect(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodLightRectNWTOSE(clrs,clr,clrfactor-0.04,fmt,x+size,y,width,height,bias,size);
		AGIDL_FloodLightRectNWTOSE(clrs,clr,clrfactor-0.08,fmt,x,y-size,width,height,bias,size);
	}
}

void AGIDL_FloodLightRectSETONE(COLOR* clrs, const COLOR clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInInvXRange(bias,x,size,width) && IsInYRange(bias,y,size,height)){
		AGIDL_FillLightRect(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodLightRectSETONE(clrs,clr,clrfactor-0.04,fmt,x-size,y,width,height,bias,size);
		AGIDL_FloodLightRectSETONE(clrs,clr,clrfactor-0.08,fmt,x,y+size,width,height,bias,size);
	}
}

void AGIDL_FloodInvLightRectNE(COLOR* clrs, const COLOR clr, float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInXRange(bias,x,size,width) && IsInYRange(bias,y,size,height)){
		clrfactor = AGIDL_Clampf(0,clrfactor,1.0f);
		AGIDL_FillLightRect(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodInvLightRectNE(clrs,clr,clrfactor+0.04,fmt,x+size,y,width,height,bias,size);
		AGIDL_FloodInvLightRectNE(clrs,clr,clrfactor+0.08,fmt,x,y+size,width,height,bias,size);
	}
}

void AGIDL_FloodInvLightRectSE(COLOR* clrs, const COLOR clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInInvXRange(bias,x,size,width) && IsInInvYRange(bias,y,size,height)){
		AGIDL_FillLightRect(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodInvLightRectSE(clrs,clr,clrfactor+0.04,fmt,x-size,y,width,height,bias,size);
		AGIDL_FloodInvLightRectSE(clrs,clr,clrfactor+0.08,fmt,x,y-size,width,height,bias,size);
	}
}

void AGIDL_FloodInvLightRectNWTOSE(COLOR* clrs, const COLOR clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInXRange(bias,x,size,width) && IsInInvYRange(bias,y,size,height)){
		AGIDL_FillLightRect(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodInvLightRectNWTOSE(clrs,clr,clrfactor+0.04,fmt,x+size,y,width,height,bias,size);
		AGIDL_FloodInvLightRectNWTOSE(clrs,clr,clrfactor+0.08,fmt,x,y-size,width,height,bias,size);
	}
}

void AGIDL_FloodInvLightRectSETONE(COLOR* clrs, const COLOR clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInInvXRange(bias,x,size,width) && IsInYRange(bias,y,size,height)){
		AGIDL_FillLightRect(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodInvLightRectSETONE(clrs,clr,clrfactor+0.04,fmt,x-size,y,width,height,bias,size);
		AGIDL_FloodInvLightRectSETONE(clrs,clr,clrfactor+0.08,fmt,x,y+size,width,height,bias,size);
	}
}

void AGIDL_FloodLightRectNE16(COLOR16* clrs, const COLOR16 clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInXRange(bias,x,size,width) && IsInYRange(bias,y,size,height)){
		AGIDL_FillLightRect16(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodLightRectNE16(clrs,clr,clrfactor-0.04,fmt,x+size,y,width,height,bias,size);
		AGIDL_FloodLightRectNE16(clrs,clr,clrfactor-0.08,fmt,x,y+size,width,height,bias,size);
	}
}

void AGIDL_FloodLightRectSE16(COLOR16* clrs, const COLOR16 clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInInvXRange(bias,x,size,width) && IsInInvYRange(bias,y,size,height)){
		AGIDL_FillLightRect16(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodLightRectSE16(clrs,clr,clrfactor-0.04,fmt,x-size,y,width,height,bias,size);
		AGIDL_FloodLightRectSE16(clrs,clr,clrfactor-0.08,fmt,x,y-size,width,height,bias,size);
	}
}

void AGIDL_FloodLightRectNWTOSE16(COLOR16* clrs, const COLOR16 clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInXRange(bias,x,size,width) && IsInInvYRange(bias,y,size,height)){
		AGIDL_FillLightRect16(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodLightRectNWTOSE16(clrs,clr,clrfactor-0.04,fmt,x+size,y,width,height,bias,size);
		AGIDL_FloodLightRectNWTOSE16(clrs,clr,clrfactor-0.08,fmt,x,y-size,width,height,bias,size);
	}
}

void AGIDL_FloodLightRectSETONE16(COLOR16* clrs, const COLOR16 clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInInvXRange(bias,x,size,width) && IsInYRange(bias,y,size,height)){
		AGIDL_FillLightRect16(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodLightRectSETONE16(clrs,clr,clrfactor-0.04,fmt,x-size,y,width,height,bias,size);
		AGIDL_FloodLightRectSETONE16(clrs,clr,clrfactor-0.08,fmt,x,y+size,width,height,bias,size);
	}
}

void AGIDL_FloodInvLightRectNE16(COLOR16* clrs, const COLOR16 clr, float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInXRange(bias,x,size,width) && IsInYRange(bias,y,size,height)){
		clrfactor = AGIDL_Clampf(0,clrfactor,1.0f);
		AGIDL_FillLightRect16(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodInvLightRectNE16(clrs,clr,clrfactor+0.04,fmt,x+size,y,width,height,bias,size);
		AGIDL_FloodInvLightRectNE16(clrs,clr,clrfactor+0.08,fmt,x,y+size,width,height,bias,size);
	}
}

void AGIDL_FloodInvLightRectSE16(COLOR16* clrs, const COLOR16 clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInInvXRange(bias,x,size,width) && IsInInvYRange(bias,y,size,height)){
		AGIDL_FillLightRect16(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodInvLightRectSE16(clrs,clr,clrfactor+0.04,fmt,x-size,y,width,height,bias,size);
		AGIDL_FloodInvLightRectSE16(clrs,clr,clrfactor+0.08,fmt,x,y-size,width,height,bias,size);
	}
}

void AGIDL_FloodInvLightRectNWTOSE16(COLOR16* clrs, const COLOR16 clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInXRange(bias,x,size,width) && IsInInvYRange(bias,y,size,height)){
		AGIDL_FillLightRect16(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodInvLightRectNWTOSE16(clrs,clr,clrfactor+0.04,fmt,x+size,y,width,height,bias,size);
		AGIDL_FloodInvLightRectNWTOSE16(clrs,clr,clrfactor+0.08,fmt,x,y-size,width,height,bias,size);
	}
}

void AGIDL_FloodInvLightRectSETONE16(COLOR16* clrs, const COLOR16 clr, const float clrfactor, const AGIDL_CLR_FMT fmt, const u16 x, const u16 y, const u16 width, const u16 height, const float bias, const u8 size){
	if(IsInInvXRange(bias,x,size,width) && IsInYRange(bias,y,size,height)){
		AGIDL_FillLightRect16(clrs,x,y,width,height,size,AGIDL_DotColor(clr,clrfactor,fmt));
		AGIDL_FloodInvLightRectSETONE16(clrs,clr,clrfactor+0.04,fmt,x-size,y,width,height,bias,size);
		AGIDL_FloodInvLightRectSETONE16(clrs,clr,clrfactor+0.08,fmt,x,y+size,width,height,bias,size);
	}
}

void AGIDL_LightInvScan(COLOR* clrs, const u16 width, const u16 height, const AGIDL_CLR_FMT fmt){
	for(u16 y = 0; y < height; y++){
		for(u16 x = 0; x < width; x++){
			const COLOR clr = AGIDL_GetClr(clrs,x,y,width,height);
			const u8 r = AGIDL_GetR(clr,fmt);
			const u8 g = AGIDL_GetG(clr,fmt);
			const u8 b = AGIDL_GetB(clr,fmt);

			if((r == 0 && g == 0 && b == 0) || (r == 245 && g == 245 && b == 245)){
				AGIDL_SetClr(clrs,AGIDL_RGB(255,255,255,fmt),x,y,width,height);
			}
		}
	}
}

void * AGIDL_GenerateLightmapImgData(const AGIDL_LIGHTMAP lightmap){
	if(AGIDL_GetBitCount(lightmap.fmt) == 24 || AGIDL_GetBitCount(lightmap.fmt) == 32){
		const u16 w = lightmap.width, h = lightmap.height;
		
		COLOR* lightdata = malloc(sizeof(COLOR)*w*h);

		const COLOR defacto = AGIDL_RGB(245,245,245,lightmap.fmt);
		AGIDL_ClrMemset(lightdata,defacto,w*h);

		for(u16 y = 0; y < h; y++){
			for(u16 x = 0; x < w; x++){
				for(u16 i = 0; i < lightmap.num_of_points; i++){
					const AGIDL_Point p = lightmap.points[i];
					if(p.x == x && p.y == y){
						const AGIDL_CLR_FMT fmt = lightmap.fmt;
						if(p.inv == 1){
							switch(p.dir){
								case LIGHT_DIR_NE:{
									AGIDL_FloodInvLightRectNE(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),0.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
								}break;
								case LIGHT_DIR_SE:{
									AGIDL_FloodInvLightRectSE(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),0.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
								}break;
								case LIGHT_DIR_NW_TO_SE:{
									AGIDL_FloodInvLightRectNWTOSE(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),0.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
								}break;
								case LIGHT_DIR_SE_TO_NW:{
									AGIDL_FloodInvLightRectSETONE(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),0.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
								}break;
							}
						}
						else{
							switch(p.dir){
								case LIGHT_DIR_NE:{
									AGIDL_FloodLightRectNE(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),1.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
								}break;
								case LIGHT_DIR_SE:{
									AGIDL_FloodLightRectSE(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),1.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
								}break;
								case LIGHT_DIR_NW_TO_SE:{
									AGIDL_FloodLightRectNWTOSE(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),1.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
								}break;
								case LIGHT_DIR_SE_TO_NW:{
									AGIDL_FloodLightRectSETONE(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),1.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
								}break;
							}
						}	
					}
				}
			}
		}
			
		AGIDL_LightInvScan(lightdata,w,h,lightmap.fmt);
			
		return lightdata;
	}
	const u16 w = lightmap.width, h = lightmap.height;

	COLOR16* lightdata = malloc(sizeof(COLOR16)*w*h);

	const COLOR16 defacto = AGIDL_RGB16(30,30,30,lightmap.fmt);
	AGIDL_ClrMemset16(lightdata,defacto,w*h);

	for(u16 y = 0; y < h; y++){
		for(u16 x = 0; x < w; x++){
			for(u16 i = 0; i < lightmap.num_of_points; i++){
				const AGIDL_Point p = lightmap.points[i];
				if(p.x == x && p.y == y){
					const AGIDL_CLR_FMT fmt = lightmap.fmt;
					if(p.inv == 1){
						switch(p.dir){
							case LIGHT_DIR_NE:{
								AGIDL_FloodInvLightRectNE16(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),0.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
							}break;
							case LIGHT_DIR_SE:{
								AGIDL_FloodInvLightRectSE16(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),0.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
							}break;
							case LIGHT_DIR_NW_TO_SE:{
								AGIDL_FloodInvLightRectNWTOSE16(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),0.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
							}break;
							case LIGHT_DIR_SE_TO_NW:{
								AGIDL_FloodInvLightRectSETONE16(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),0.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
							}break;
						}
					}
					else{
						switch(p.dir){
							case LIGHT_DIR_NE:{
								AGIDL_FloodLightRectNE16(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),1.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
							}break;
							case LIGHT_DIR_SE:{
								AGIDL_FloodLightRectSE16(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),1.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
							}break;
							case LIGHT_DIR_NW_TO_SE:{
								AGIDL_FloodLightRectNWTOSE16(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),1.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
							}break;
							case LIGHT_DIR_SE_TO_NW:{
								AGIDL_FloodLightRectSETONE16(lightdata,AGIDL_GrayscaleColor(p.clr,fmt),1.0f,lightmap.fmt,x,y,w,h,p.bias,p.size);
							}break;
						}
					}
				}
			}
		}
	}

	//AGIDL_LightInvScan(lightdata,w,h,lightmap.fmt);

	return lightdata;
}
