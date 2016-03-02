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
 * Name: JSONDefinitions.h
 *
 * Overview: Interface that contains the required definitions for
 * the JSON messages creation process. This code depends on the 
 * protocol defined to interact between the Mentor System and the
 * Trainee System; is that protocol were to change (add or remove
 * fields in the protocol), those changes will have to be made into
 * these definitions
 */
///////////////////////////////////////////////////////////////////

//Define guards
#ifndef JSON_DEFINITIONS_H
#define JSON_DEFINITIONS_H

//---------------------General JSON Keywords---------------------//
#ifndef JSON_FILE_LOCATION
#define JSON_FILE_LOCATION "../JSON_Files/json.txt"
#endif

#ifndef INDENTATION
#define INDENTATION "indentation"
#endif

#ifndef NO_INDENTATION
#define NO_INDENTATION ""
#endif

#ifndef TAB_INDENTATION
#define TAB_INDENTATION "\t"
#endif

#ifndef POLYLINE_CODE
#define POLYLINE_CODE 1
#endif

#ifndef RESOLUTION_X
#define RESOLUTION_X 1920.0
#endif

#ifndef RESOLUTION_Y
#define RESOLUTION_Y 1080.0
#endif

//------------------Mentor System JSON Keywords------------------//
#ifndef ID
#define ID "id"
#endif

#ifndef COMMAND
#define COMMAND "command"
#endif

#ifndef ANNOTATION_MEMORY
#define ANNOTATION_MEMORY "annotation_memory"
#endif

#ifndef MATCHES
#define MATCHES "matches"
#endif

#ifndef INITIAL_KEY_POINTS
#define INITIAL_KEY_POINTS "initialKeyPoints"
#endif

#ifndef INITIAL_DESCRIPTORS
#define INITIAL_DESCRIPTORS "initialDescriptors"
#endif

#ifndef INITIAL_ANNOTATION
#define INITIAL_ANNOTATION "initialAnnotation"
#endif

#ifndef INITIAL_POINTS
#define INITIAL_POINTS "annotationPoints"
#endif

#ifndef SCALE
#define SCALE "scale"
#endif

#ifndef ANNOTATION_TYPE
#define ANNOTATION_TYPE "annotationType"
#endif

#ifndef TOOL_TYPE
#define TOOL_TYPE "toolType"
#endif

#ifndef ROTATION
#define ROTATION "rotation"
#endif

#ifndef SELECTABLE_COLOR
#define SELECTABLE_COLOR "selectableColor"
#endif

#ifndef CURRENT_ANNOTATION
#define CURRENT_ANNOTATION "currentAnnotation"
#endif

#ifndef CURRENT_HOMOGRAPHY
#define CURRENT_HOMOGRAPHY "currentHomography"
#endif

#ifndef INITIAL_RAW_KEY_POINTS
#define INITIAL_RAW_KEY_POINTS "initialRawKeyPoints"
#endif

#ifndef CURRENT_RAW_KEY_POINTS
#define CURRENT_RAW_KEY_POINTS "currentRawKeyPoints"
#endif

#ifndef X_COORDINATE
#define X_COORDINATE "x"
#endif

#ifndef Y_COORDINATE
#define Y_COORDINATE "y"
#endif

//-------------------------Command Types-------------------------//
#ifndef CREATE_ANNOTATION_COMMAND
#define CREATE_ANNOTATION_COMMAND "CreateAnnotationCommand"
#endif

#ifndef UPDATE_ANNOTATION_COMMAND
#define UPDATE_ANNOTATION_COMMAND "UpdateAnnotationCommand"
#endif

#ifndef DELETE_ANNOTATION_COMMAND
#define DELETE_ANNOTATION_COMMAND "DeleteAnnotationCommand"
#endif

#ifndef REQUEST_START_TRACKING_COMMAND
#define REQUEST_START_TRACKING_COMMAND "RequestStartTrackingCommand"
#endif

#ifndef REQUEST_STOP_TRACKING_COMMAND
#define REQUEST_STOP_TRACKING_COMMAND "RequestStopTrackingCommand"
#endif

#ifndef REQUEST_START_SENDING_FRAMES_COMMAND
#define REQUEST_START_SENDING_FRAMES_COMMAND "RequestStartSendingFramesCommand"
#endif

#ifndef REQUEST_STOP_SENDING_FRAMES_COMMAND
#define REQUEST_STOP_SENDING_FRAMES_COMMAND "RequestStopSendingFramesCommand"
#endif

//------------------------Annotation Types-----------------------//
#ifndef POINT_ANNOTATION
#define POINT_ANNOTATION "point"
#endif

#ifndef MULTI_POINT_ANNOTATION
#define MULTI_POINT_ANNOTATION "multi_point"
#endif

#ifndef POLYLINE_ANNOTATION
#define POLYLINE_ANNOTATION "polyline"
#endif

#ifndef POLYGON_ANNOTATION
#define POLYGON_ANNOTATION "polygon"
#endif

#ifndef VIRTUAL_TOOL_ANNOTATION
#define VIRTUAL_TOOL_ANNOTATION "tool"
#endif


//--------------------Virtual Annotation Types-------------------//
#ifndef BVM
#define BVM "bvm"
#endif

#ifndef ETTUBE
#define ETTUBE "ettube"
#endif

#ifndef HEMOSTAT
#define HEMOSTAT "hemostat"
#endif

#ifndef IODINESWAB
#define IODINESWAB "iodineswab"
#endif

#ifndef RETRACTOR
#define RETRACTOR "retractor"
#endif

#ifndef SCALPEL
#define SCALPEL "scalpel"
#endif

#ifndef STETHOSCOPE
#define STETHOSCOPE "stethoscope"
#endif

#ifndef SURGICALTAPE
#define SURGICALTAPE "surgicaltape"
#endif

#ifndef SYRINGE
#define SYRINGE "syringe"
#endif

#ifndef TWEEZERS
#define TWEEZERS "tweezers"
#endif

#ifndef LONGHOOK
#define LONGHOOK "longhook"
#endif

#ifndef SCISSORS
#define SCISSORS "scissors"
#endif

#ifndef TEXT_CLOSE
#define TEXT_CLOSE "text_close"
#endif

#ifndef TEXT_INCISION
#define TEXT_INCISION "text_incision"
#endif

#ifndef TEXT_PALPATION
#define TEXT_PALPATION "text_palpation"
#endif

#ifndef TEXT_REMOVE
#define TEXT_REMOVE "text_remove"
#endif

#ifndef TEXT_STITCH
#define TEXT_STITCH "text_stitch"
#endif

#ifndef HAND_PALPATE
#define HAND_PALPATE "hand_palpate"
#endif

#ifndef HAND_POINT
#define HAND_POINT "hand_point"
#endif

#ifndef HAND_STRETCH
#define HAND_STRETCH "hand_stretch"
#endif

#endif
