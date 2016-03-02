///////////////////////////////////////////////////////////////////
/*
 * Mentor System Application
 * System for Telemementoring with Augmented Reality (STAR) Project
 * Intelligent Systems and Assistive Technology (ISAT) Laboratory
 * Purdue University School of Industrial Engineering
 * 
 * Code programmed by: Edgar Javier Rojas Muñoz
 * advised by the professor: Juan Pablo Wachs, Ph.D
 */
//---------------------------------------------------------------//
/*                        CODE OVERVIEW
 * Name: virtualAnnotationDefinitions.h
 *
 * Overview: Interface that contains the required definitions to
 * create, select and use the virtual anotations. It includes the
 * path in which the .png are and the codes assigned to each
 * annotation. The codes created are based on the specific image
 * used for the virtual annotation panel. Therefore, if the image
 * changes, these codes will need to change too.
 */
///////////////////////////////////////////////////////////////////

//Define guards
#ifndef VIRTUAL_ANNOTATION_DEFINITIONS_H
#define VIRTUAL_ANNOTATION_DEFINITIONS_H

//--------------------Images Path Definitions--------------------//
//Path to the bvm selected image
#ifndef BVM_SELECTED_IMAGE_PATH
#define BVM_SELECTED_IMAGE_PATH "../images/bvm_selected.png"
#endif

//Path to the bvm shadow image
#ifndef BVM_SHADOW_IMAGE_PATH
#define BVM_SHADOW_IMAGE_PATH "../images/bvm_shadow.png"
#endif

//Path to the ettube selected image
#ifndef ETTUBE_SELECTED_IMAGE_PATH
#define ETTUBE_SELECTED_IMAGE_PATH "../images/ettube_selected.png"
#endif

//Path to the ettube shadow image
#ifndef ETTUBE_SHADOW_IMAGE_PATH
#define ETTUBE_SHADOW_IMAGE_PATH "../images/ettube_shadow.png"
#endif

//Path to the hemostat selected image
#ifndef HEMOSTAT_SELECTED_IMAGE_PATH
#define HEMOSTAT_SELECTED_IMAGE_PATH "../images/hemostat_selected.png"
#endif

//Path to the hemostat shadow image
#ifndef HEMOSTAT_SHADOW_IMAGE_PATH
#define HEMOSTAT_SHADOW_IMAGE_PATH "../images/hemostat_shadow.png"
#endif

//Path to the iodine swab selected image
#ifndef IODINE_SWAB_SELECTED_IMAGE_PATH
#define IODINE_SWAB_SELECTED_IMAGE_PATH "../images/iodineswab_selected.png"
#endif

//Path to the iodine swab shadow image
#ifndef IODINE_SWAB_SHADOW_IMAGE_PATH
#define IODINE_SWAB_SHADOW_IMAGE_PATH "../images/iodineswab_shadow.png"
#endif

//Path to the longhook selected image
#ifndef LONGHOOK_SELECTED_IMAGE_PATH
#define LONGHOOK_SELECTED_IMAGE_PATH "../images/longhook_selected.png"
#endif

//Path to the longhook shadow image
#ifndef LONGHOOK_SHADOW_IMAGE_PATH
#define LONGHOOK_SHADOW_IMAGE_PATH "../images/longhook_shadow.png"
#endif

//Path to the retractor selected image
#ifndef RETRACTOR_SELECTED_IMAGE_PATH
#define RETRACTOR_SELECTED_IMAGE_PATH "../images/retractor_selected.png"
#endif

//Path to the retractor shadow image
#ifndef RETRACTOR_SHADOW_IMAGE_PATH
#define RETRACTOR_SHADOW_IMAGE_PATH "../images/retractor_shadow.png"
#endif

//Path to the scalpel selected image
#ifndef SCALPEL_SELECTED_IMAGE_PATH
#define SCALPEL_SELECTED_IMAGE_PATH "../images/scalpel_selected.png"
#endif

//Path to the scalpel shadow image
#ifndef SCALPEL_SHADOW_IMAGE_PATH
#define SCALPEL_SHADOW_IMAGE_PATH "../images/scalpel_shadow.png"
#endif

//Path to the scissors selected image
#ifndef SCISSORS_SELECTED_IMAGE_PATH
#define SCISSORS_SELECTED_IMAGE_PATH "../images/scissors_selected.png"
#endif

//Path to the scissors shadow image
#ifndef SCISSORS_SHADOW_IMAGE_PATH
#define SCISSORS_SHADOW_IMAGE_PATH "../images/scissors_shadow.png"
#endif

//Path to the stethoscope selected image
#ifndef STETHOSCOPE_SELECTED_IMAGE_PATH
#define STETHOSCOPE_SELECTED_IMAGE_PATH "../images/stethoscope_selected.png"
#endif

//Path to the stethoscope shadow image
#ifndef STETHOSCOPE_SHADOW_IMAGE_PATH
#define STETHOSCOPE_SHADOW_IMAGE_PATH "../images/stethoscope_shadow.png"
#endif

//Path to the surgical tape selected image
#ifndef SURGICAL_TAPE_SELECTED_IMAGE_PATH
#define SURGICAL_TAPE_SELECTED_IMAGE_PATH "../images/surgicaltape_selected.png"
#endif

//Path to the surgical tape shadow image
#ifndef SURGICAL_TAPE_SHADOW_IMAGE_PATH
#define SURGICAL_TAPE_SHADOW_IMAGE_PATH "../images/surgicaltape_shadow.png"
#endif

//Path to the syringe selected image
#ifndef SYRINGE_SELECTED_IMAGE_PATH
#define SYRINGE_SELECTED_IMAGE_PATH "../images/syringe_selected.png"
#endif

//Path to the syringe shadow image
#ifndef SYRINGE_SHADOW_IMAGE_PATH
#define SYRINGE_SHADOW_IMAGE_PATH "../images/syringe_shadow.png"
#endif

//Path to the tweezers selected image
#ifndef TWEEZERS_SELECTED_IMAGE_PATH
#define TWEEZERS_SELECTED_IMAGE_PATH "../images/tweezers_selected.png"
#endif

//Path to the tweezers shadow image
#ifndef TWEEZERS_SHADOW_IMAGE_PATH
#define TWEEZERS_SHADOW_IMAGE_PATH "../images/tweezers_shadow.png"
#endif

//Path to the hand point selected image
#ifndef HAND_POINT_SELECTED_IMAGE_PATH
#define HAND_POINT_SELECTED_IMAGE_PATH "../images/hand_point_selected.png"
#endif

//Path to the hand point shadow image
#ifndef HAND_POINT_SHADOW_IMAGE_PATH
#define HAND_POINT_SHADOW_IMAGE_PATH "../images/hand_point_shadow.png"
#endif

//Path to the hand strech selected image
#ifndef HAND_STRETCH_SELECTED_IMAGE_PATH
#define HAND_STRETCH_SELECTED_IMAGE_PATH "../images/hand_strech_selected.png"
#endif

//Path to the hand strech shadow image
#ifndef HAND_STRETCH_SHADOW_IMAGE_PATH
#define HAND_STRETCH_SHADOW_IMAGE_PATH "../images/hand_strech_shadow.png"
#endif

//Path to the hand palpate selected image
#ifndef HAND_PALPATE_SELECTED_IMAGE_PATH
#define HAND_PALPATE_SELECTED_IMAGE_PATH "../images/hand_palpate_selected.png"
#endif

//Path to the hand palpate shadow image
#ifndef HAND_PALPATE_SHADOW_IMAGE_PATH
#define HAND_PALPATE_SHADOW_IMAGE_PATH "../images/hand_palpate_shadow.png"
#endif

//Path to the text close selected image
#ifndef TEXT_CLOSE_SELECTED_IMAGE_PATH
#define TEXT_CLOSE_SELECTED_IMAGE_PATH "../images/text_close_selected.png"
#endif

//Path to the text close shadow image
#ifndef TEXT_CLOSE_SHADOW_IMAGE_PATH
#define TEXT_CLOSE_SHADOW_IMAGE_PATH "../images/text_close_shadow.png"
#endif

//Path to the text incision selected image
#ifndef TEXT_INCISION_SELECTED_IMAGE_PATH
#define TEXT_INCISION_SELECTED_IMAGE_PATH "../images/text_incision_selected.png"
#endif

//Path to the text incision shadow image
#ifndef TEXT_INCISION_SHADOW_IMAGE_PATH
#define TEXT_INCISION_SHADOW_IMAGE_PATH "../images/text_incision_shadow.png"
#endif

//Path to the text palpation selected image
#ifndef TEXT_PALPATION_SELECTED_IMAGE_PATH
#define TEXT_PALPATION_SELECTED_IMAGE_PATH "../images/text_palpation_selected.png"
#endif

//Path to the text palpation shadow image
#ifndef TEXT_PALPATION_SHADOW_IMAGE_PATH
#define TEXT_PALPATION_SHADOW_IMAGE_PATH "../images/text_palpation_shadow.png"
#endif

//Path to the text remove selected image
#ifndef TEXT_REMOVE_SELECTED_IMAGE_PATH
#define TEXT_REMOVE_SELECTED_IMAGE_PATH "../images/text_remove_selected.png"
#endif

//Path to the text remove shadow image
#ifndef TEXT_REMOVE_SHADOW_IMAGE_PATH
#define TEXT_REMOVE_SHADOW_IMAGE_PATH "../images/text_remove_shadow.png"
#endif

//Path to the text stitch selected image
#ifndef TEXT_STITCH_SELECTED_IMAGE_PATH
#define TEXT_STITCH_SELECTED_IMAGE_PATH "../images/text_stitch_selected.png"
#endif

//Path to the text stitch shadow image
#ifndef TEXT_STITCH_SHADOW_IMAGE_PATH
#define TEXT_STITCH_SHADOW_IMAGE_PATH "../images/text_stitch_shadow.png"
#endif

//----------------Panel Interpretation Definitions---------------//
//First row
#ifndef FIRST_ROW_CODE
#define FIRST_ROW_CODE 1
#endif

//Second row
#ifndef SECOND_ROW_CODE
#define SECOND_ROW_CODE 2
#endif

//Third row
#ifndef THIRD_ROW_CODE
#define THIRD_ROW_CODE 3
#endif

//Fourth row
#ifndef FOURTH_ROW_CODE
#define FOURTH_ROW_CODE 4
#endif

//Fifth row
#ifndef FIFTH_ROW_CODE
#define FIFTH_ROW_CODE 5
#endif

//Sixth row
#ifndef SIXTH_ROW_CODE
#define SIXTH_ROW_CODE 6
#endif

//Seventh row
#ifndef SEVENTH_ROW_CODE
#define SEVENTH_ROW_CODE 7
#endif

//First column
#ifndef FIRST_COLUMN_CODE
#define FIRST_COLUMN_CODE 7
#endif

//Second column
#ifndef SECOND_COLUMN_CODE
#define SECOND_COLUMN_CODE 8
#endif

//Third column
#ifndef THIRD_COLUMN_CODE
#define THIRD_COLUMN_CODE 9
#endif

//--------------------Virtual annotation code--------------------//
//Note that these codes are calculated as row_value x column_value
//bvm
#ifndef BVM_CODE
#define BVM_CODE 7
#endif

//ettube
#ifndef ETTUBE_CODE
#define ETTUBE_CODE 8
#endif

//hemostat
#ifndef HEMOSTAT_CODE
#define HEMOSTAT_CODE 9
#endif

//iodine swab
#ifndef IODINE_SWAB_CODE
#define IODINE_SWAB_CODE 14
#endif

//longhook
#ifndef LONGHOOK_CODE
#define LONGHOOK_CODE 16
#endif

//retractor
#ifndef RETRACTOR_CODE
#define RETRACTOR_CODE 18
#endif

//scalpel
#ifndef SCALPEL_CODE
#define SCALPEL_CODE 21
#endif

//scissors
#ifndef SCISSORS_CODE
#define SCISSORS_CODE 24
#endif

//stethoscope
#ifndef STETHOSCOPE_CODE
#define STETHOSCOPE_CODE 27
#endif

//surgical tape
#ifndef SURGICAL_TAPE_CODE
#define SURGICAL_TAPE_CODE 28
#endif

//syringe
#ifndef SYRINGE_CODE
#define SYRINGE_CODE 32
#endif

//tweezers
#ifndef TWEEZERS_CODE
#define TWEEZERS_CODE 36
#endif

//hand point
#ifndef HAND_POINT_CODE
#define HAND_POINT_CODE 35
#endif

//hand stretch
#ifndef HAND_STRETCH_CODE
#define HAND_STRETCH_CODE 40
#endif

//hand palpate
#ifndef HAND_PALPATE_CODE
#define HAND_PALPATE_CODE 45
#endif

//text close
#ifndef TEXT_CLOSE_CODE
#define TEXT_CLOSE_CODE 42
#endif

//text incision
#ifndef TEXT_INCISION_CODE
#define TEXT_INCISION_CODE 48
#endif

//text palpation
#ifndef TEXT_PALPATION_CODE
#define TEXT_PALPATION_CODE 54
#endif

//text remove
#ifndef TEXT_REMOVE_CODE
#define TEXT_REMOVE_CODE 49
#endif

//text stitch
#ifndef TEXT_STITCH_CODE
#define TEXT_STITCH_CODE 56
#endif

//-------------------------Anchor Points-------------------------//
//Bvm X anchor point
#ifndef BVM_X_ANCHOR
#define BVM_X_ANCHOR 63
#endif

//Bvm Y anchor point
#ifndef BVM_Y_ANCHOR
#define BVM_Y_ANCHOR 119
#endif

//Ettube X anchor point
#ifndef ETTUBE_X_ANCHOR
#define ETTUBE_X_ANCHOR 42
#endif

//Ettube Y anchor point
#ifndef ETTUBE_Y_ANCHOR
#define ETTUBE_Y_ANCHOR 168
#endif

//Hemostat X anchor point
#ifndef HEMOSTAT_X_ANCHOR
#define HEMOSTAT_X_ANCHOR 6
#endif

//Hemostat Y anchor point
#ifndef HEMOSTAT_Y_ANCHOR
#define HEMOSTAT_Y_ANCHOR 125
#endif

//Iodine swab X anchor point
#ifndef IODINE_SWAB_X_ANCHOR
#define IODINE_SWAB_X_ANCHOR 44
#endif

//Iodine swab Y anchor point
#ifndef IODINE_SWAB_Y_ANCHOR
#define IODINE_SWAB_Y_ANCHOR 47
#endif

//Longhook X anchor point
#ifndef LONGHOOK_X_ANCHOR
#define LONGHOOK_X_ANCHOR 33
#endif

//Longhook Y anchor point
#ifndef LONGHOOK_Y_ANCHOR
#define LONGHOOK_Y_ANCHOR 24
#endif

//Retractor X anchor point
#ifndef RETRACTOR_X_ANCHOR
#define RETRACTOR_X_ANCHOR 47
#endif

//Retractor Y anchor point
#ifndef RETRACTOR_Y_ANCHOR
#define RETRACTOR_Y_ANCHOR 164
#endif

//Scalpel X anchor point
#ifndef SCALPEL_X_ANCHOR
#define SCALPEL_X_ANCHOR 9
#endif

//Scalpel Y anchor point
#ifndef SCALPEL_Y_ANCHOR
#define SCALPEL_Y_ANCHOR 25
#endif

//Scissors X anchor point
#ifndef SCISSORS_X_ANCHOR
#define SCISSORS_X_ANCHOR 15
#endif

//Scissors Y anchor point
#ifndef SCISSORS_Y_ANCHOR
#define SCISSORS_Y_ANCHOR 96
#endif

//Stethoscope X anchor point
#ifndef STETHOSCOPE_X_ANCHOR
#define STETHOSCOPE_X_ANCHOR 92
#endif

//Stethoscope Y anchor point
#ifndef STETHOSCOPE_Y_ANCHOR
#define STETHOSCOPE_Y_ANCHOR 320
#endif

//Surgical tape X anchor point
#ifndef SURGICAL_TAPE_X_ANCHOR
#define SURGICAL_TAPE_X_ANCHOR 51
#endif

//Surgical tape Y anchor point
#ifndef SURGICAL_TAPE_Y_ANCHOR
#define SURGICAL_TAPE_Y_ANCHOR 294
#endif

//Syringe X anchor point
#ifndef SYRINGE_X_ANCHOR
#define SYRINGE_X_ANCHOR 9
#endif

//Syringe Y anchor point
#ifndef SYRINGE_Y_ANCHOR
#define SYRINGE_Y_ANCHOR 55
#endif

//Tweezers X anchor point
#ifndef TWEEZERS_X_ANCHOR
#define TWEEZERS_X_ANCHOR 21
#endif

//Tweezers Y anchor point
#ifndef TWEEZERS_Y_ANCHOR
#define TWEEZERS_Y_ANCHOR 43
#endif

//Hand point X anchor point
#ifndef HAND_POINT_X_ANCHOR
#define HAND_POINT_X_ANCHOR 12
#endif

//Hand point Y anchor point
#ifndef HAND_POINT_Y_ANCHOR
#define HAND_POINT_Y_ANCHOR 19
#endif

//Hand stretch X anchor point
#ifndef HAND_STRETCH_X_ANCHOR
#define HAND_STRETCH_X_ANCHOR 36
#endif

//Hand stretch Y anchor point
#ifndef HAND_STRETCH_Y_ANCHOR
#define HAND_STRETCH_Y_ANCHOR 120
#endif

//Hand palpate X anchor point
#ifndef HAND_PALPATE_X_ANCHOR
#define HAND_PALPATE_X_ANCHOR 16
#endif

//Hand palpate Y anchor point
#ifndef HAND_PALPATE_Y_ANCHOR
#define HAND_PALPATE_Y_ANCHOR 19
#endif

//Text close X anchor point
#ifndef TEXT_CLOSE_X_ANCHOR
#define TEXT_CLOSE_X_ANCHOR 105
#endif

//Text close Y anchor point
#ifndef TEXT_CLOSE_Y_ANCHOR
#define TEXT_CLOSE_Y_ANCHOR 31
#endif

//Text incision X anchor point
#ifndef TEXT_INCISION_X_ANCHOR
#define TEXT_INCISION_X_ANCHOR 155
#endif

//Text incision Y anchor point
#ifndef TEXT_INCISION_Y_ANCHOR
#define TEXT_INCISION_Y_ANCHOR 32
#endif

//Text palpation X anchor point
#ifndef TEXT_PALPATION_X_ANCHOR
#define TEXT_PALPATION_X_ANCHOR 189
#endif

//Text palpation Y anchor point
#ifndef TEXT_PALPATION_Y_ANCHOR
#define TEXT_PALPATION_Y_ANCHOR 39
#endif

//Text remove X anchor point
#ifndef TEXT_REMOVE_X_ANCHOR
#define TEXT_REMOVE_X_ANCHOR 152
#endif

//Text remove Y anchor point
#ifndef TEXT_REMOVE_Y_ANCHOR
#define TEXT_REMOVE_Y_ANCHOR 25
#endif

//Text stitch X anchor point
#ifndef TEXT_STITCH_X_ANCHOR
#define TEXT_STITCH_X_ANCHOR 114
#endif

//Text stitch Y anchor point
#ifndef TEXT_STITCH_Y_ANCHOR
#define TEXT_STITCH_Y_ANCHOR 33
#endif

#endif