/*------------------------------------------------------------------------------*
 * File Name: DescStats.c	 													*
 * Creation: ML 4/7/03															*
 * Purpose: OriginC Source C file for auto update descriptive statistics.		*
 * Copyright (c) OriginLab Corp.	2003-2007									*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 * Danice 5/5/04 QA70-6341 v8.0865 SETREPORTTREE_ENABLE_CONTROL					*
 *	CPY 5/6/04 QA70-6367 HISTOGRAM_GRAPHS										*
 *	ML 8/17/2004 QA70-6825 RLOG_QUERY											*
 *  Iris 9/10/04 REPLACE_WITH_GLOBAL_FUNCTION									*
 *  Iris 9/23/04 MOVE_INTERPOLATE_TO_COMPUTATION_BRANCH							*
 *	YuI 10/18/04 QA70-70-60 v7.5151 NON_HIERARCHY_GRID_SHOULD_NOT_ADD_UNWANTED_COLUMNS	*
 *	CPY 11/3/04	QA70-7122 ADD_BOX_CHART_TO_DESC_STATS							*
 *  Iris 11/10/04 CENTRALIZE_CODE_INTO_STATSOPBASE_HEADER						*
 *  Iris 12/20/04 MOVE_TO_COMPCONTROL_BRANCH									*
 *	Echo 1/31/05 OUTPUT_TABLE_TRANSPOSE											*
 *	Echo 2/2/05 BAD_WEIGHT_TREAMENT												*
 *  Iris 3/22/05 FIX_GROUP_DATA_ONLY_ONE_BOX_CHART								*
 *  Iris 3/22/05 UPDATE_COLUMN_LABEL_FOR_GROUP_DATA								*
 *	Thomas 6/1/06 REDEFINE_UPDATEDATASOURCEINREPORTINGHEADER_FOR_DESCSTATS		*
 *  Iris 06/06/06 DIFF_INPUT_FORMAT_FOR_COL_AND_ROW								*
 *  Alex 06/13/06 SET_EXTREME_VALUES_TABLE_OPEN                                 *
 *  Iris 7/11/06 QA70-6367-P5 DIFF_RESULT_SHEET_NAME_FOR_COLS_AND_ROWS			*
 *	CPY 10/14/06 SEPARATE_OUT_OPERATION_BASE_INTO_SEPARATE_HEADER				*
 *  Iris 11/03/06 NO_NEED_PLOTS_FOR_STATS_ON_ROWS								*
 *  Iris 4/18/2007 v8.0603 ADD_OUTPUT_DEST_COL_OPTION_STATS_ON_ROWS				*
 *  Iris 05/14/2007 v8.0617 NOT_OUTPUT_INDEX_TEMP								*
 *	Cheney 2007-5-14 NOT_SUPPORT_SEP_REPORT_IN_STATS_ON_COL						*
 *  Iris 05/18/2007 v8.0621 CORRECT_BAD_LOOP									*
 *	Cheney 2007-5-23 QA70-9805 SPEED_UP_STATISTIC_ON_ROW						*
 *	Cheney 2007-6-7 SHOULD_CHECK_EVENT_ID_IN_EVENT_FUNC							*
 *	Arvin 06/19/07 WRONG_HISTOGRAM_AND_BOXCHART_PLOTS_WHILE_DATA_HAVE_FACTORS	*
 *	Arvin 07/25/07 v8.0667 WRONG_INPUT_DATA_TABLE_FOR_MULTI_DATA_AND_FACTORS	*
 *	Arvin 08/14/07 v8.0681 WRONG_MAX_AND_MIN_INDEX_IN_QUANTILES_WHEN_DATA_HAS_FACTORS
 *	Arvin 08/14/07 WRONG_HISTOGRAM_AND_BOXCHART_PLOT_WHEN_COMBINED_MUTI_AS_SINGLE_DATASET
 *	Arvin 08/22/07 WRONG_HISTOGRAM_SCALE_IN_STATS_ON_COL						*
 *	Arvin 08/24/07 SHOULD_NOT_CREATE_NEW_RESULT_SHEET_FOR_AUTO_UPDATE			*
 *	Cheney 2007-8-31 QA70-10330 CLEAN_UP_PLOT_SETTING_BRANCH_IN_OUTPUT_RESULT_NODE
 *	Arvin 08/31/07 QA70-7651-P17 WRONG_COLUMN_DESIGNATION_TYPE					*
 *	Arvin 08/31/07 PDS_CUSTOM_CAN_NOT_WORK_IN_STATS_ON_ROWS						*
 *	Arvin 09/03/07 WRONG_WEIGHT_LABEL_IN_MASK_AND_MISSING_DATA_TABLE			*
 *	Arvin 11/10/07 XOP_NEED_SUPPORT_CHANGE_FUNCTION								*
 *	Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID		*
 *	Max 07-11-17 NEED_TO_CHECK_CUSTOMPERCENTILES_NODE							*
 *	Fisher 11/19/07 ADD_MAP_ID_TO_CHM											*
 *	ML 11/20/2007 QA70-10716 INPUT_DATA_NODE_PROPER_LANGUAGE_WHEN_LOADING_OPER	*
 *  Iris 3/26/2008 v8.0832 CLEANUP_OUTPUT_BOOK_SHEET_AREA_TO_CLASS				*
 *	Folger 05/30/08 QA80-11624 SHOW_WARNING_FOR_TURN_OFF_AUTO_UPDATE_IN_STATS_ON_ROWS
 *  Iris 9/11/2008 FIX_SHOW_ERR_MSG_FOR_CONTIGUOUS_MULTI_RANGES_FOR_STATS_ON_ROWS*
 *	Hong 11/19/08 QA80-12558 V8.90875 DESC_STATS_ON_COL_SUPPORT_DATA_FROM_GRAPH	*
 *	Sophy 12/17/2008 v8.0987d  QA80-12784 ADD_BINNING_CONTROL_FOR_HISTOGRAM_PLOT_IN_STATS_TOOLS
 *	Sophy 1/5/2009 v8.0993d QA80-12858 GIVE_USEFUL_INFO_ON_REPORT_GRAPH_WITH_FACTOR_VALUE_FOR_STATS_COLUMN
 *	Folger 01/21/09 RESET_ALL_GRAPHS_FAILS_TO_PLOT_HISTOGRAM_IN_NLFIT			*
 *	Sophy 1/23/2009 v8.0964b CLEAN_UP_PLOT_SETTING_BRANCH_IN_OUTPUT_RESULT_NODE	*
 *  Iris 2/19/2009 QA_FOUND_RUNTIME_ERR_IF_CMOBI_SOURCE_DATA_AND_REPORT_INCLUDED_GRAPH
 *	Sophy 4/3/2009 QA80-13352 SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
 *  Iris 4/07/2009 QA80-12784 IMPROVE_HISTOGRAM_CONFIG_BRANCH					*
 *  Iris 9/10/2009 QA80-11710-P2 IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA
 *  Iris 10/16/2009 QA80-14484 BOX_HISTOGRAM_ALSO_NEED_KEEP_CUSTOMIZATION_WHEN_RECALCULATION
 *  Iris 10/28/2009 QA81-14546 CHANGE_GUI_REPORT_TABLE_LABEL					*
 *  Iris 11/05/2009 QA81-14599 FIX_STATS_ON_COLS_PLOT_REPORT_GRAPHS_VERY_SLOW	*
 *  Iris 11/09/2009 QA81-14599 IMPROVE_STATS_ON_COLS_CALCULATION_SPEED			*
 *	Hong 11/27/09 QA80-14752 FIX_HISTOGRAM_BAD_RESCALE_IF_GRAPH_SHOWN_BEFORE_RECACULATE_WHEN_DATA_CHANGE
 *	Hong 12/11/09 QA80-14138-P2 FIX_STATS_ON_COL_CHANGE_PARAM_CANNOT_ADD_BACK_MISSING_TABLE
 *  Iris 2/22/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS	*
 *	Folger 03/24/10 QA81-15224 STATS_ON_ROWS_FAILED_TO_UPDATE_COL_HEADERS_WHEN_RECALCULATE
 *	Folger 10/12/2010 ORG-1240-P1 FAILED_TO_SHOW_WEIGHT_DATA_IN_REPORT_INPUT_OTHER_THAN_FIRST_DATA
 *	Folger 10/15/2010 INPUT_DATA_BRANCH_IN_DESC_STATS_SHOULD_BE_OPEN_BE_DEFAULT	*
 *  Iris 11/05/2010 ORG-1368-P1 CHANGE_DATA_MODE_IN_CHANGE_PARAM_CAUSE_REPORT_GRAPH_NOT_CORRECT
 *  Iris 11/19/2010 ORG-1535-P1 FOUND_EMPTY_EXTREME_VALUES_REPORT_TABLE_IN_CHANGE_PARAMS
 *	Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
 *  Iris 3/18/2011 ORG-2427 STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT				*
 *  Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX		*
 *  Iris 8/29/2011 ORG-3645-P1 FIX_STATS_ON_ROWS_FAIL_TO_OPEN_DLG				*
 *  Iris 9/09/2011 ORG2427-P5 FIX_FLAT_SHEET_NOT_UPDATED_IN_RECALCULATE			*
 *  Iris 9/21/2011 ORG-2427-P6 FIX_FLAT_REPORT_ONLY_ONE_DATA_RESULT				*
 *  Iris 10/09/2011 ORG-4047-P1 FIX_NO_FLAT_REPORT_STILL_ADD_RESULT_TO_OPERATION_TREE*
 *  Iris 10/11/2011 ORG-4047-P1 CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
 *	Folger 11/01/2011 ORG-3997-P1 TRANSLATE_OP_STRING_ON_FLAT_SHEET_WHEN_DELETE_DESCSTATS_OPERATION
 *	Folger 05/16/2012 ORG-5592-S3 ADD_DATA_IDENTIFIER_FOR_STATS_TOOLS			*
 *	Folger 05/31/2012 ORG-5592-S1 SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET			*
 *	Folger 06/06/2012 ORG-5906-P1 NORMALITY_TEST_TOO_SLOW_FOR_LARGE_DATA		*
 *	Folger 08/02/2012 ORG-6412-S1 XF_REPORT_DATA_SET_COLUMN_SHORT_NAME_CONTROL	*
 *	Folger 08/24/2012 ORG-6311-P1 UPDATE_DATASET_INDENTIFIER_FOR_FLAT_SHEET_FROM_CONTEXT_MENU
 *	Zech 09/12/2012 ORG-5703-P3 FIX_EXTREME_VALUE_INDEX_IN_STATISTICS_IN_COLUMN	*
 *	Folger 09/17/2012 ORG-6829-P1 FAILED_TO_SHOW_SUB_DATA_INDEX_IN_STATS_ON_COLUMN_REPORT_SHEET
 *  Iris 10/22/2012 ORG-7175-P1 FIX_NO_EXTREME_TABLE_CREATED_AFTER_SELECTED_THE_TABEL_IN_CHANGE_PARAM
 *  Iris 11/16/2012 ORG-7449-P1 IMPROVE_STATS_ON_COL_CHANGE_PARAM_SPEED			*
 *  Iris 11/22/2012 ORG-7518-P1 IMPROVE_STATS_ON_COLS_EVNET_SPEED				*
 *	Philip 11/26/2012 ORG-7525-P1 FIX_FAIL2CALC_CUSTOMPERCENT_IN_STAT_ON_COL	*
 *	Folger 11/29/2012 ORG-7570-P1 SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION	*
 *	Folger 12/13/2012 ORG-7618-P3 PROPER_SHOW_DATASET_IDENTIFIER_IN_FLAT_SHEET_IF_MORE_THAN_ONE_USER_PARAM
 *	Folger 01/22/2013 ORG-7350-P1 STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
 *	Folger 05/02/2013 ORG-8563-P1 DATASET_ID_LABEL_ROW_FAILED_TO_SHOW_IN_STATS_ON_COLUMN
 *	Folger 05/03/2013 ORG-8566-P1 STATS_ON_COLUMN_FAILED_IF_NO_OUTPUT			*
 *	Damon 7/24/2013 ORG-8473-S4 v9.100148c PLOT_IN_ONE_CHECKED_BY_DEFAULT		*
 *	Damon 8/20/2013 ORG-9265-P1 FIX_GUI_FOR_STATS_ON_ROWS						*
 *	Folger 08/23/2013 ORG-8566-P1 STATS_ON_COLUMN_FAILED_IF_NO_OUTPUT			*
 *	Hong 05/21/2014 ORG-11155 OPERATION_RESULT_COPY_CATEGORICAL_INFO			*
 *	Kyle 05/29/2014 ORG-10284-S1 TRIM_MISSING_BLANK_VALUES_FROM_GROUPING_COLUMN	*
 *	Folger 06/12/2014 ORG-11276-P1 STATS_ON_COLUMNS_OUTPUT_FLAT_SHEET_ALLOW_REORDER
 *	Folger 08/20/2014 ORG-4941-P1 DESCSTATS_SHOULD_NOT_OUTPUT_FLAT_REPORT_FOR_OPJ_BEFORE_86
 *  Iris 09/11/2014 ORG-11749-S1 ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS	*
 *------------------------------------------------------------------------------*/
 
//////////////////////////////////////////////////////////////////////////////////
// Included header files
//////////////////////////////////////////////////////////////////////////////////

// System includes
#include <Origin.h>
#include <event_utils.h> //CPY
#include <report_utils.h>

#ifdef _FOR_SMART_LOADING_ONLY
#include "wksOperation.h" //---- CPY 10/14/06 SEPARATE_OUT_OPERATION_BASE_INTO_SEPARATE_HEADER
#include <analysis_utils.h>
#include <stats_utils.h>
#include "stats_guis.h"
#include "stats_operations.h"
//#include "graph_utils.h" 	///Arvin 03/08/07 AXIS_TITILE_SHOULD_ADD_FACTOR_INFO_IN_HISTOGRAM_GRAPH
#endif
#include <xfutils.h>
#include "StatsOpCommon.h"
#include "StatsOpBase.h"
#include "graph_utils.h" ///Arvin 03/08/07 AXIS_TITILE_SHOULD_ADD_FACTOR_INFO_IN_HISTOGRAM_GRAPH
/// Iris 09/11/2014 ORG-11749-S1 ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS
#include "wks_utils.h"
/// End ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS

#define		STR_NEXT_TO_SOURCE		_L("<next to source>")
//---- CPY 5/6/04 QA70-6367 HISTOGRAM_GRAPHS
#define STR_DESC_STATS_GRAPH_TEMPLATE "ReportDescStats"	
///Cheney 2007-5-23 QA70-9805 SPEED_UP_STATISTIC_ON_ROW
enum{
	DESC_STATS_ON_COLS,
	DESC_STATS_ON_ROWS,
};
///end SPEED_UP_STATISTIC_ON_ROW

typedef struct tagExVals
{  
	int _id(1) 		Index;
	double _id(2) 	Value;
}ExVals;

/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
#define OUTPUT_SOURCE_DATA_RESULT_SHEET			OUTPUT_RESULT_START
#define OUTPUT_FLAT_RESULT_SHEET				OUTPUT_RESULT_START + 1
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX

/// Iris 11/22/2012 ORG-7518-P1 IMPROVE_STATS_ON_COLS_EVNET_SPEED
#define NO_DATA					-1
#define IS_NUM_OF_DATA_NOT_CHECKED(nn)		(NO_DATA == nn)
static int s_nNumDataset = NO_DATA;
static int s_nNumDataPoint = -1; // the number not the real number of data points, only used to check data number == 0 or not. 
static vector<int> s_vFactorSizes(0);
///End IMPROVE_STATS_ON_COLS_EVNET_SPEED

///------ Folger 02/04/2020 ORG-21417-P1 STATS_ON_COLUMNS_PROPER_REPORT_DATA_COLUMN_IDS
#define TOTAL_NUMBER_OF_REPORT_DATA_COL_ID (IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL_MORE_END - IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL_MORE_BEGIN + 1 + 1)
static int _GetReportDataColID(int ii)
{
	if (0 == ii)
		return IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL;
	int nID = ii - 1 + IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL_MORE_BEGIN;
	if (nID > IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL_MORE_END)
	{
		ASSERT(FALSE);
		return 0;
	}
	return nID;
}
///------ End STATS_ON_COLUMNS_PROPER_REPORT_DATA_COLUMN_IDS

///Cheney 2007-8-31 QA70-10330 CLEAN_UP_PLOT_SETTING_BRANCH_IN_OUTPUT_RESULT_NODE
static bool _on_input_data_change(TreeNode& tr, int nRow, int nCol, TreeNode& trNode, int nEventInfo, int nCntrlType, WndContainer& getNContainer
								, DataRange& drData ///------ Folger 01/22/2013 ORG-7350-P1 STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
								  )
{
	if(!tr)
		return false;
	
	///Sophy 8/25/2011 ORG-3644-P1 IMPROVE_GUI_DISPLAY_ON_CHANGE_SETTINGS_WHEN_CHANGE_PARAM
	TreeNode trNodeUpdate = tree_get_node(tr, nRow);
	bool bInputChange = false;	
	/// Iris 09/11/2014 ORG-11749-S1 ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS
	//if ( trNodeUpdate && (trNodeUpdate.tagName == "X" || trNodeUpdate.tagName == "F" || trNodeUpdate.tagName == "W") )
	if ( trNodeUpdate && 
		( trNodeUpdate.tagName == "X" 
		|| trNodeUpdate.tagName == "F" 
		|| trNodeUpdate.tagName == "W"
		|| trNodeUpdate.tagName == "List"
		)
	)
	/// End ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS
		bInputChange = true;
	///end IMPROVE_GUI_DISPLAY_ON_CHANGE_SETTINGS_WHEN_CHANGE_PARAM
	
	/// Iris 09/11/2014 ORG-11749-S1 ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS
	if( GETNE_ON_VALUE_CHANGE == nEventInfo && "List" == trNodeUpdate.tagName )
	{
		///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
		if(tr.StatsOnRows.nVal)
			update_GetN_range_from_label_list_ctrls(trNodeUpdate, tr.InputData.Range1.F);	
		else
		///End STATS_ON_ROWS_SUPPORT_GROUPING
		update_GetN_range_from_col_list_ctrls(trNodeUpdate, tr.InputData.Range1.F);	
	}
	/// End ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS
	
	/// Iris 3/25/2011 ORG-2528-P1 FIX_BOXCHART_PLOT_IN_ONE_GRAPH_ISSUE_IN_STATS_ON_COLS
	if( is_change_parameter(tr) && nRow > 0 )
	{		
		///Sophy 8/25/2011 ORG-3644-P1 IMPROVE_GUI_DISPLAY_ON_CHANGE_SETTINGS_WHEN_CHANGE_PARAM
		//TreeNode trN = tree_get_node(tr, nRow);
		//if( trN.tagName == "X" || trN.tagName == "F" || trN.tagName == "W" ) // input data changed
		///Kyle 08/07/2015 ORG-12921-P1 STATS_ON_COL_SKIP_EMPTY_OUTPUT_PLOTS
		//if ( bInputChange )
		if ( bInputChange || trNodeUpdate && trNodeUpdate.tagName == "ExcludeEmpty" )
		///End STATS_ON_COL_SKIP_EMPTY_OUTPUT_PLOTS
		///end IMPROVE_GUI_DISPLAY_ON_CHANGE_SETTINGS_WHEN_CHANGE_PARAM
		{
			foreach(TreeNode trGraph in tr.Plots.Children)
			{			
				trGraph.SetAttribute(STR_RESET_GRAPH_ATTRIB, 1);
			}
		}
	}
	///End FIX_BOXCHART_PLOT_IN_ONE_GRAPH_ISSUE_IN_STATS_ON_COLS
	
	/// Iris 11/05/2010 ORG-1368-P1 CHANGE_DATA_MODE_IN_CHANGE_PARAM_CAUSE_REPORT_GRAPH_NOT_CORRECT
	if( nEventInfo == GETNE_ON_INIT ) // enter to below when before open dialog
	{
		int nDataMode;
		if( tr.InputData.GetAttribute(STR_USE_ATTRIB, nDataMode) )
		{
			tr.InputData.SetAttribute("LastUsedDataMode", nDataMode);
		}
	}
	///End CHANGE_DATA_MODE_IN_CHANGE_PARAM_CAUSE_REPORT_GRAPH_NOT_CORRECT
	
	/// Iris 11/22/2012 ORG-7518-P1 IMPROVE_STATS_ON_COLS_EVNET_SPEED
	/*
	TreeNode trRange = tr.InputData.Range1;
	DataRange drData;
	drData.Create();
	drData.SetTree(trRange, DRTREE_ONE_DATA);
	if (!drData.IsValid())
		return false;

	/// Iris 9/10/2009 QA80-11710-P2 IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA
	//int nNumData = drData.GetNumData(DRR_BAD_WEIGHT_TREATMENT);		
	vector<int> vFactorSizes;	
	int nNumData = drData.GetNumData(DRR_BAD_WEIGHT_TREATMENT, NULL, NULL, &vFactorSizes);					
	///end IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA
	*/	
	if( nEventInfo == GETNE_ON_INIT || bInputChange || IS_NUM_OF_DATA_NOT_CHECKED(s_nNumDataset) )
	{		
		TreeNode trRange = tr.InputData.Range1;
		///------ Folger 01/22/2013 ORG-7350-P1 STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
		//DataRange drData;
		if ( !drData )
		///------ End STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
		{
			drData.Create();
			drData.SetTree(trRange, DRTREE_ONE_DATA);
		}
		
		///------ Folger 10/21/2020 ORG-22656-P4 STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
		//s_nNumDataset = check_get_num_data(drData, tr, nRow, nEventInfo, DRR_BAD_WEIGHT_TREATMENT, s_nNumDataset, NULL, &s_vFactorSizes);
		DWORD dwRules = DRR_BAD_WEIGHT_TREATMENT;
		if (tr.StatsOnRows.nVal)
			dwRules |= DRR_BY_ROWS;
		s_nNumDataset = check_get_num_data(drData, tr, nRow, nEventInfo, dwRules, s_nNumDataset, NULL, &s_vFactorSizes);
		///------ End STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
		
		s_nNumDataPoint = -1; // reset the variable, it will be reinit in another function below			
	}
	///End IMPROVE_STATS_ON_COLS_EVNET_SPEED	
		
	/// Iris 10/29/2009 QA81-14546 OP_DLG_NEW_STRUCTURE
	//TreeNode trGraphNumCols = tr.Output.PlotSettings.GraphNumCols;
	TreeNode trGraphNumCols = OP_GUI_GRAPH_ARRANGEMENT_NODE(tr).GraphNumCols;
	///end OP_DLG_NEW_STRUCTURE
	
	///Sophy 5/30/2008 FIX_BOOKNAME_EMPTY_FOR_SOURCE_TYPE_WHEN_NO_DATA_SELECTED_OPEN_DIALOG
	/*
	if(!trGraphNumCols)
		return false;
	
	///Cheney 2007-11-19 ARRANGE_GRAPH_COLS_NUM_NOT_WORK
	//int nAutoCheck = octree_get_auto_support(&trGraphNumCols);
	//if( !(nAutoCheck == 1 && trGraphNumCols.nVal > 0) )
		//trGraphNumCols.nVal = get_report_graph_num_cols(nNumData);
	if(1 == octree_get_auto_support(&trGraphNumCols))
		trGraphNumCols.nVal = get_report_graph_num_cols(nNumData);
	///end ARRANGE_GRAPH_COLS_NUM_NOT_WORK
	*/
	bool	bRet = false;
	if( trGraphNumCols )
	{
		if( 1 == octree_get_auto_support( &trGraphNumCols ) )
		{
			/// Iris 9/10/2009 QA80-11710-P2 IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA
			//trGraphNumCols.nVal = get_report_graph_num_cols( nNumData );
			/// Iris 9/22/2011 ORG-3208-S1 FIX_REPORT_GRAPH_ISSUE_FOR_MISSED_FACTOR_IN_MULTI_GROUPS_DATA
			// change the code in order to support multi groups data
			//int nNumFactors = vFactorSizes.GetSize() > 0 ? vFactorSizes[0] : 0;						
			int nNumFactors = 0;
			/// Iris 11/22/2012 ORG-7518-P1 IMPROVE_STATS_ON_COLS_EVNET_SPEED
			/*
			if( vFactorSizes.GetSize() > 0 )
			{
				nNumFactors = vFactorSizes[0];
				int index = 1;
				while(index < vFactorSizes.GetSize())
				{
					nNumFactors *= vFactorSizes[index++];
				}
			}
			*/
			if( s_vFactorSizes.GetSize() > 0 )
			{
				nNumFactors = s_vFactorSizes[0];
				int index = 1;
				while(index < s_vFactorSizes.GetSize())
				{
					nNumFactors *= s_vFactorSizes[index++];
				}
			}
			///End IMPROVE_STATS_ON_COLS_EVNET_SPEED
			///End FIX_REPORT_GRAPH_ISSUE_FOR_MISSED_FACTOR_IN_MULTI_GROUPS_DATA
			/// Iris 10/29/2009 QA81-14546 OP_DLG_NEW_STRUCTURE
			//TreeNode trPlotInOne = tr.Output.PlotSettings.PlotInOneGraph;
			TreeNode trPlotInOne = OP_GUI_GRAPH_ARRANGEMENT_NODE(tr).PlotInOneGraph;
			///end OP_DLG_NEW_STRUCTURE
			bool bPlotInOne = trPlotInOne && trPlotInOne.Show && trPlotInOne.nVal;
			/// Iris 11/22/2012 ORG-7518-P1 IMPROVE_STATS_ON_COLS_EVNET_SPEED
			//trGraphNumCols.nVal = get_report_graph_num_cols( nNumData, nNumFactors, bPlotInOne );
			//ASSERT( !IS_NUM_OF_DATA_NOT_CHECKED(s_nNumDataset) );
			trGraphNumCols.nVal = get_report_graph_num_cols( s_nNumDataset, nNumFactors, bPlotInOne );
			///End IMPROVE_STATS_ON_COLS_EVNET_SPEED
			///end IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA
		}
		
		bRet = true;
	}
	///end FIX_BOOKNAME_EMPTY_FOR_SOURCE_TYPE_WHEN_NO_DATA_SELECTED_OPEN_DIALOG
	///Cheney 2007-10-16 QA70-10536 CLEAN_CODE_AND_FIX_BUG_OF_ADD_AUTO_FOR_OUTPUT_SETTING
	/// Iris 3/21/2008 v8.0829 QA80-10934 ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME, parameter changed from trOp to trGUI
	//string strSrcPageName = get_source_page_name(tr.Parent());
	string strSrcPageName = get_source_page_name(tr);
	///end ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
	
#ifndef _MOVE_FIT_OUTPUT_TO_OC_CLASS /// Iris 3/26/2008 v8.0832 CLEANUP_OUTPUT_BOOK_SHEET_AREA_TO_CLASS
	update_output_report_and_curve_setting(tr, strSrcPageName);
#else
	///Sophy 8/25/2011 ORG-3644-P1 IMPROVE_GUI_DISPLAY_ON_CHANGE_SETTINGS_WHEN_CHANGE_PARAM
	/// Iris 4/22/2015 ORG-12835-P1 FIX_LOAD_THEME_FILE_CANNOT_CORRECTLY_UPDATE_SOURCE_BOOKSHEET_NAME
	//if ( bInputChange )
	if( bInputChange || nEventInfo == GETNE_ON_THEME )
	///End FIX_LOAD_THEME_FILE_CANNOT_CORRECTLY_UPDATE_SOURCE_BOOKSHEET_NAME
	{
	///end IMPROVE_GUI_DISPLAY_ON_CHANGE_SETTINGS_WHEN_CHANGE_PARAM
	OutputGUIManagerBase* pOutputManager = get_output_GUI_manager_pointer(tr);
	if(pOutputManager)
		///Sophy 04/09/2008 UPDATEOUTPUT_ON_DATA_CHANGE
		//pOutputManager->UpdateOutputReportAndCurveSetting(tr,strSrcPageName);
		pOutputManager->UpdateOutputOnDataChange(tr);
		///End UPDATEOUTPUT_ON_DATA_CHANGE
	///Sophy 8/25/2011 ORG-3644-P1 IMPROVE_GUI_DISPLAY_ON_CHANGE_SETTINGS_WHEN_CHANGE_PARAM
	}
	///end IMPROVE_GUI_DISPLAY_ON_CHANGE_SETTINGS_WHEN_CHANGE_PARAM
#endif //_MOVE_FIT_OUTPUT_TO_OC_CLASS

	///------ Folger 05/16/2012 ORG-5592-S3 ADD_DATA_IDENTIFIER_FOR_STATS_TOOLS
	if ( bInputChange || GETNE_ON_INIT == nEventInfo || GETNE_ON_THEME == nEventInfo )
	{
		op_update_data_identifiers(tr, tr.InputData);
	}
	///------ End ADD_DATA_IDENTIFIER_FOR_STATS_TOOLS
	
	///end CLEAN_CODE_AND_FIX_BUG_OF_ADD_AUTO_FOR_OUTPUT_SETTING
	///Sophy 5/30/2008 FIX_BOOKNAME_EMPTY_FOR_SOURCE_TYPE_WHEN_NO_DATA_SELECTED_OPEN_DIALOG
	//return true;
	return bRet;
	///end FIX_BOOKNAME_EMPTY_FOR_SOURCE_TYPE_WHEN_NO_DATA_SELECTED_OPEN_DIALOG
}
///end CLEAN_UP_PLOT_SETTING_BRANCH_IN_OUTPUT_RESULT_NODE

///------ Folger 01/22/2013 ORG-7350-P1 STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
//static int _desc_stats_check_data(TreeNode trRange)
static int _desc_stats_check_data(TreeNode trRange, DataRange& drData)
///------ End STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
{
	if (!trRange)
		return CER_COL_NUM_TOO_FEW_EX;
	///------ Folger 01/22/2013 ORG-7350-P1 STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
	//DataRange drData;
	if ( !drData )
	///------ End STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
	{
		drData.Create();
		drData.SetTree(trRange, DRTREE_ONE_DATA);
	}

	if (drData)
	{
		DWORD dwRules = DRR_BAD_WEIGHT_TREATMENT;
		DWORD dwPlotID;
		/// Iris 11/22/2012 ORG-7518-P1 IMPROVE_STATS_ON_COLS_EVNET_SPEED
		//int nNumData = drData.GetNumData(dwRules);		
		if( IS_NUM_OF_DATA_NOT_CHECKED(s_nNumDataset) )
		{
			//ASSERT(false);
			s_nNumDataset = drData.GetNumData(dwRules);
			s_nNumDataPoint = -1;
		}
		int nNumData = s_nNumDataset;
		///End IMPROVE_STATS_ON_COLS_EVNET_SPEED
		if (nNumData < 1)		
			return CER_COL_NUM_TOO_FEW_EX;
			
		int nSize = 0;
		/// Iris 11/22/2012 ORG-7518-P1 IMPROVE_STATS_ON_COLS_EVNET_SPEED
		/*
		vector vData;		
		for (int ii = 0; ii < nNumData; ii++)		
		{
			drData.GetData(dwRules, ii, &dwPlotID, NULL, &vData, NULL, NULL, NULL);
			nSize += vData.GetSize();	
		}
		*/
		if( s_nNumDataPoint < 0 )
		{
			vector vData;		
			for (int ii = 0; ii < nNumData; ii++)		
			{
				drData.GetData(dwRules, ii, &dwPlotID, NULL, &vData, NULL, NULL, NULL);
				nSize += vData.GetSize();
				/// Iris 9/19/2014 ORG-11749-P3 FIX_SLOW_SPEED_WHEN_CHANGE_THE_ORDER_OF_COLS_IN_GROUP_RANGE_CTRL
				// nSize only used to check if there is no data, so when find nSize != 0 to avoid multiple times loop, 
				if( nSize > 0 )
					break;
				///End FIX_SLOW_SPEED_WHEN_CHANGE_THE_ORDER_OF_COLS_IN_GROUP_RANGE_CTRL
			}			
				
			s_nNumDataPoint = nSize;
		}
		else
		{
			nSize = s_nNumDataPoint;
		}
		///End IMPROVE_STATS_ON_COLS_EVNET_SPEED
		if (0 == nSize)
			return CER_NO_DATA;			
	}
}

/// Iris 5/20/2015 ORG-12835-P9 FIX_STATS_ON_ROWS_CANNOT_SET_TO_AUTOUPDATE_ONE_SET_AS_NONE
// moved it to tree_utils.c file
/*
//------ Folger 05/30/08 QA80-11624 SHOW_WARNING_FOR_TURN_OFF_AUTO_UPDATE_IN_STATS_ON_ROWS
static	bool	_auto_update_need_turn_off(const DataRange &dr, LPCSTR lpcszBook, LPCSTR lpcszSheet)
{
		string		strRange;
		dr.GetRangeString(strRange);		// only single range is available
		
		string		strBook, strSheet, strObj;
		okutil_parse_complete_range_string(strRange, &strBook, &strSheet, &strObj);
		
		string strC1, strC2, strR1, strR2;
		okutil_parse_range_string(strObj, &strC1, &strR1, &strC2, &strR2);
		
		if ( !strC1.IsEmpty() || !strC2.IsEmpty() )		// case A[1]:B[2]
			return false;
		
		string			strBookSheet1 = okutil_make_book_sheet_string(strBook, strSheet);
		string			strBookSheet2 = okutil_make_book_sheet_string(lpcszBook, lpcszSheet);
		Worksheet		wks1, wks2;
		okxf_resolve_string_get_origin_object(strBookSheet1, &wks1);
		okxf_resolve_string_get_origin_object(strBookSheet2, &wks2);
		
		if ( is_same_layer(wks1, wks2) )
			return true;
	
	return false;
}
//------ End SHOW_WARNING_FOR_TURN_OFF_AUTO_UPDATE_IN_STATS_ON_ROWS
*/
///End FIX_STATS_ON_ROWS_CANNOT_SET_TO_AUTOUPDATE_ONE_SET_AS_NONE

///Joseph 01/29/07	ADD_OPERATION_ERRMSG_LINE
static int descstats_event1(TreeNode& tr, int nRow, int nEvent, DWORD& dwEnables, LPCSTR lpcszNodeName, WndContainer& getNCountainer, string& strAux, string& strErrMsg)
{
	DataRange drData; ///------ Folger 01/22/2013 ORG-7350-P1 STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP

	DECLARE_BUTTON_ENABLES	
	///Cheney 2007-5-23 QA70-9805 SPEED_UP_STATISTIC_ON_ROW
	//int nErr = check_1_data(tr.InputData.Range1.X, true);
	//if ( !check_conf_level(tr.Quantities.Quantiles.PercentileList.strVal) )
	int nErr = CER_NO_ERROR; 
	/// Sophy 5/08/2008 FIX_BUG_REPORT_BOOK_BLANK_WHEN_NO_DATUM_SELECTED_IN_STATS_ON_COLUMN
	/// Iris 11/05/2010 ORG-1368-P1 CHANGE_DATA_MODE_IN_CHANGE_PARAM_CAUSE_REPORT_GRAPH_NOT_CORRECT
	//_on_input_data_change( tr,nRow,0,NULL,0,0,getNCountainer);
	//_on_input_data_change(tr, nRow, 0, NULL, nEvent, 0, getNCountainer);
	///------ Folger 01/22/2013 ORG-7350-P1 STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
	_on_input_data_change(tr, nRow, 0, NULL, nEvent, 0, getNCountainer, drData);
	///------ End STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
	///End CHANGE_DATA_MODE_IN_CHANGE_PARAM_CAUSE_REPORT_GRAPH_NOT_CORRECT
	/// End FIX_BUG_REPORT_BOOK_BLANK_WHEN_NO_DATUM_SELECTED_IN_STATS_ON_COLUMN
	///Cheney 2007-6-7 SHOULD_CHECK_EVENT_ID_IN_EVENT_FUNC	
	///Cheney 2007-7-6 SHOULD_CHECK_ERR_WHEN_THEME_CHANGE_ALSO
	//if(GETNE_ON_VALUE_CHANGE == nEvent  || GETNE_ON_INIT == nEvent)
	
	/// Iris 4/07/2009 QA80-12784 IMPROVE_HISTOGRAM_CONFIG_BRANCH
	/*
	///Sophy 12/19/2008 v8.0987d  QA80-12784 ADD_BINNING_CONTROL_FOR_HISTOGRAM_PLOT_IN_STATS_TOOLS fix bin config not updated when change input data
	string strNodeName(lpcszNodeName);
	if ( strNodeName.CompareNoCase("X") == 0 )
	{
		TreeNode trHistogramConfig = tr.Output.GetNode(STR_HISTOGRAM_CONFIG_TAGNAME);
		_update_histogram_plot_bin_configuration_by_input(tr, trHistogramConfig);
	}
	///end ADD_BINNING_CONTROL_FOR_HISTOGRAM_PLOT_IN_STATS_TOOLS
	*/	
	/// Iris 11/22/2012 ORG-7518-P1 IMPROVE_STATS_ON_COLS_EVNET_SPEED
	//_update_histogram_bin_info_in_event1(tr, lpcszNodeName, nEvent);
	//ASSERT( !IS_NUM_OF_DATA_NOT_CHECKED(s_nNumDataset) );
	_update_histogram_bin_info_in_event1(tr, lpcszNodeName, nEvent, s_nNumDataset);
	///End IMPROVE_STATS_ON_COLS_EVNET_SPEED
	///end IMPROVE_HISTOGRAM_CONFIG_BRANCH
	
	bool	bAutoUpdateTurnOff = false;		//------ Folger 05/30/08 QA80-11624 SHOW_WARNING_FOR_TURN_OFF_AUTO_UPDATE_IN_STATS_ON_ROWS
	
	///------ Folger 10/15/2010 INPUT_DATA_BRANCH_IN_DESC_STATS_SHOULD_BE_OPEN_BE_DEFAULT
	/// Easwar suggested that input data branch in Stats On Column should be open by default
	if ( GETNE_ON_INIT == nEvent )
	{
		TreeNode	trRange1 = tr.InputData.Range1;
		if ( trRange1 )
		{
			int		nBranch = 0;
			trRange1.GetAttribute(STR_ATTRIB_BRANCH, nBranch);
			if ( 0 == nBranch )
				trRange1.SetAttribute(STR_ATTRIB_BRANCH, GETNBRANCH_OPEN);
		}
	}
	///------ End INPUT_DATA_BRANCH_IN_DESC_STATS_SHOULD_BE_OPEN_BE_DEFAULT
	
	if(GETNE_ON_VALUE_CHANGE == nEvent  || GETNE_ON_INIT == nEvent || GETNE_ON_THEME == nEvent)
	///end SHOULD_CHECK_ERR_WHEN_THEME_CHANGE_ALSO
	///end SHOULD_CHECK_EVENT_ID_IN_EVENT_FUNC
	{		
		TreeNode trRange = tr.InputData.Range1;
		TreeNode trX = trRange.X;
		if(!trRange)
			nErr = CER_INVALID_TREENODE;
		
		if(nErr == CER_NO_ERROR && DESC_STATS_ON_ROWS != tr.StatsOnRows.nVal)
		{
			///------ Folger 01/22/2013 ORG-7350-P1 STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
			//nErr = _desc_stats_check_data(trRange);
			nErr = _desc_stats_check_data(trRange, drData);
			///------ End STATS_ON_COLUMNS_TOO_SLOW_TO_GENERATE_CATEGORICAL_MAP
			
			/// Iris 4/28/2015 ORG-12969-P1 ADD_WARINING_MSG_WHEN_OUTPUT_RESULT_TO_SOURCE_SHEET
			if ( nErr == CER_NO_ERROR && tr.Output.FlatOut.Book && tr.Output.FlatOut.Sheet )
			{
				string strBookName, strSheetName;
				int nBookType = str_to_predefined_type(tr.Output.FlatOut.Book.strVal, &strBookName);
				int nSheetType = str_to_predefined_type(tr.Output.FlatOut.Sheet.strVal, &strSheetName);
				
				/// Iris 5/27/2015 ORG-12835-P10 FIX_STATS_ON_COLS_FAIL_TO_PREVENT_REPORT_TO_SOURCE
				//if( PDS_SOURCE == nBookType && PDS_SOURCE == nSheetType && !strBookName.IsEmpty() && !strSheetName.IsEmpty() )
				if( !strBookName.IsEmpty() && !strSheetName.IsEmpty() )
				///End FIX_STATS_ON_COLS_FAIL_TO_PREVENT_REPORT_TO_SOURCE
					bAutoUpdateTurnOff = auto_update_need_turn_off(drData, strBookName, strSheetName);
			}
			///End ADD_WARINING_MSG_WHEN_OUTPUT_RESULT_TO_SOURCE_SHEET
		}
		else if(nErr == CER_NO_ERROR)
		{
			Range dr;
			bool 	bRet = okxf_resolve_tree_construct_range(&trX, &dr);			
			bool	bIsContiguousRange = dr.ConvertToContiguous(); //-- Iris 9/11/2008 FIX_SHOW_ERR_MSG_FOR_CONTIGUOUS_MULTI_RANGES_FOR_STATS_ON_ROWS
			
			if(nErr == CER_NO_ERROR)
			{
				int nNumData = dr.GetNumData(DRR_GET_MISSING /*| DRR_NO_FACTORS*/ | DRR_NO_WEIGHTS | DRR_BY_ROWS);	///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
				switch(nNumData)
				{
				///------ Folger 05/12/2020 ORG-21828-S1 STATS_ON_ROWS_SUPPORT_INPUT_FROM_DIFF_WKS
				//case EXTRACTBYROWSERR_MULTIPLE_SHEETS:
					//nErr = CER_EXTRACTBYROWSERR_MULTIPLE_SHEETS;
					//break;
				///------ End STATS_ON_ROWS_SUPPORT_INPUT_FROM_DIFF_WKS
				///------ Folger 11/27/2017 ORG-17439-S1 BETTER_INPUT_ERROR_CHECKING_FOR_STATS_ON_ROWS
				//case EXTRACTBYROWSERR_UNEVEN_COLUMNS:
					//nErr = CER_EXTRACTBYROWSERR_UNEVEN_COLUMNS;
					//break;
				///------ End BETTER_INPUT_ERROR_CHECKING_FOR_STATS_ON_ROWS
				///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
				case EXTRACTBYROWSERR_INVALID_FACTORS:
					nErr = CER_TO_FEW_FACTOR;
				///End STATS_ON_ROWS_SUPPORT_GROUPING
				default:
				}				
				
				if(nErr == CER_NO_ERROR && nNumData <= 0)
				{
					//as talk to Echo and Max, we don't support Non_contiguous ranges when stats on row
					//-- Iris 9/11/2008 FIX_SHOW_ERR_MSG_FOR_CONTIGUOUS_MULTI_RANGES_FOR_STATS_ON_ROWS
					//if(!trX.strVal.IsEmpty())
						//nErr = CER_NOT_SUPPORT_NON_CONTIGUOUS_RANGES;
					if(!trX.strVal.IsEmpty())
					{
						/// Iris 2/22/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS
						/*
						if(!bIsContiguousRange)
							nErr = CER_NOT_SUPPORT_NON_CONTIGUOUS_RANGES;
						*/
						///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS
					}
					//--
					else
						nErr = CER_NO_DATA;
				}				
				
				/// Iris 2/22/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS
				/*
				//------ Folger 05/30/08 QA80-11624 SHOW_WARNING_FOR_TURN_OFF_AUTO_UPDATE_IN_STATS_ON_ROWS
				//-- Iris 9/11/2008 FIX_SHOW_ERR_MSG_FOR_CONTIGUOUS_MULTI_RANGES_FOR_STATS_ON_ROWS
				//if ( nErr == CER_NO_ERROR && dr.GetNumRanges() > 1 )
				if ( nErr == CER_NO_ERROR && !bIsContiguousRange )
				//--	
					nErr = CER_NOT_SUPPORT_NON_CONTIGUOUS_RANGES;
				//------
				*/
				///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS
			}

			//------ Folger 05/30/08 QA80-11624 SHOW_WARNING_FOR_TURN_OFF_AUTO_UPDATE_IN_STATS_ON_ROWS
			if ( nErr == CER_NO_ERROR )
				bAutoUpdateTurnOff = auto_update_need_turn_off(dr, tr.Output.Report.BookName.strVal, tr.Output.Report.SheetName.strVal);
			//------
			
			///------ Tony 12/26/2017 ORG-10099-P3 WHEN_INPUT_DISCONTINUOUS_NOT_SUPPORT_GROUP
			if ( nErr == CER_NO_ERROR )
			{
				int nNumRange = dr.GetNumRanges();
				if(nNumRange > 1)
				{
					string strCombo;
					trRange.List.GetAttribute(STR_COMBO_ATTRIB, strCombo);
					if(strCombo.Compare(STR_NONE) != 0)
					{
						nErr = CER_GROUP_RANGE_NOT_SUPPORTED_WHEN_DATA_RANGE_DISCONTINUOUS;
					}
				}
				
			}
			///------ End WHEN_INPUT_DISCONTINUOUS_NOT_SUPPORT_GROUP
		}
		///// !!! make sure the above error checking all are input data relative /////		
		check_set_error_attribute(tr.InputData, nErr);
		
		if ( nErr == CER_NO_ERROR && !check_conf_level(tr.Quantities.Quantiles.PercentileList.strVal) )
		///end SPEED_UP_STATISTIC_ON_ROW
		{
			nErr = CER_CONF_LEVS;
		}
		
		///Sophy 4/11/2008 CHECK_REPORT_DATA_BOOK_NAME_DIFFERENT
		string strRet = "";
		if( CER_NO_ERROR == nErr )
		{
			nErr =check_report_book_curve_book( tr, strRet );
		}
		///end CHECK_REPORT_DATA_BOOK_NAME_DIFFERENT
		
		///Sophy 12/17/2008 v8.0987d  QA80-12784 ADD_BINNING_CONTROL_FOR_HISTOGRAM_PLOT_IN_STATS_TOOLS
		if ( CER_NO_ERROR == nErr )
		{
			//if ( !check_histogram_config_bin_min_max(tr) )
				//nErr = CER_MIN_MAX;
			nErr = _check_histogram_plot_bin_configuration(tr, strRet);
		}
		///end ADD_BINNING_CONTROL_FOR_HISTOGRAM_PLOT_IN_STATS_TOOLS
		if (nErr != CER_NO_ERROR)
		{
			bOKEnable = false;
			strErrMsg = nErr;
			if (nErr == CER_COL_NUM_TOO_FEW_EX)
				strErrMsg += ":" + 1;
			///Sophy 4/14/2008 ADD_OUTPUT_ERR_STRING
			else if( !strRet.IsEmpty() )
			{
				strErrMsg = nErr;
				strErrMsg += ":" + strRet;  
			}
			///end ADD_OUTPUT_ERR_STRING
		}
		
		//------ Folger 05/30/08 QA80-11624 SHOW_WARNING_FOR_TURN_OFF_AUTO_UPDATE_IN_STATS_ON_ROWS
		if ( nErr == CER_NO_ERROR && bAutoUpdateTurnOff )
		{
			strErrMsg = WARN_AUTO_UPDATE_TURN_OFF_STATS_ON_ROWS;
			
			/// YuI 06/03/08 need to actually turn it off
			tr.AutoUpdate.nVal=AU_NONE;
			/// end YuI
		}
		//------
	}
	return true;

}///End ADD_OPERATION_ERRMSG_LINE
//////////////////////////////////////////////////////////////////////////////////
// Class DescStats
//////////////////////////////////////////////////////////////////////////////////

///------ Folger 08/20/2014 ORG-4941-P1 DESCSTATS_SHOULD_NOT_OUTPUT_FLAT_REPORT_FOR_OPJ_BEFORE_86
#define VER_DESCSTATS_OP			2.0
#define STR_OP_NAME_DESCSTATS_OP	STR_OPERATION_CLASS_DESCSTATS
///------ End DESCSTATS_SHOULD_NOT_OUTPUT_FLAT_REPORT_FOR_OPJ_BEFORE_86

typedef string (*PFN_GET_LABEL_NAME_BY_TYPE)(const int nType, const Worksheet& wks = NULL);	///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING

class OC_REGISTERED DescStats : public StatsOpBase
{	
///Arvin 11/10/07 XOP_NEED_SUPPORT_CHANGE_FUNCTION
public:	
	///------ Folger 08/20/2014 ORG-4941-P1 DESCSTATS_SHOULD_NOT_OUTPUT_FLAT_REPORT_FOR_OPJ_BEFORE_86
	DescStats()
	{
		m_mvCur.AddVersion(STR_OP_NAME_DESCSTATS_OP, VER_DESCSTATS_OP);
	}
	///------ End DESCSTATS_SHOULD_NOT_OUTPUT_FLAT_REPORT_FOR_OPJ_BEFORE_86
	//Need call this method from oc code, so move it to public session
	void ClearOutputTables(TreeNode& trOperation)
	{
		StatsOpBase::ClearOutputTables(trOperation);
		
		if(trOperation.Calculation.ExVals)
			trOperation.Calculation.ExVals.Reset(true);
	}
///end XOP_NEED_SUPPORT_CHANGE_FUNCTION

protected:	
	/// Iris 10/28/2009 QA81-14546 CHANGE_GUI_REPORT_TABLE_LABEL
	/*
	/// Iris 4/17/2008 SPECIAL_REPORT_TABLE_NAME_FOR_DIFF_TOOLS
	//virtual	
	string	GetReportTableGUIName(TreeNode& trGUI)
	{
		return STR_OUTPUT_DESC_STATS_REPORT_TABLE;
	}
	///end SPECIAL_REPORT_TABLE_NAME_FOR_DIFF_TOOLS
	*/
	///end CHANGE_GUI_REPORT_TABLE_LABEL	
	
protected:	
	/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
#ifdef __STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
	//virtual
	bool	applyThemeToResultCurveTable(TreeNode& trOp, Worksheet& wksOutput)
	{
		if( wksOutput )
			return theme_set_label_merge(wksOutput, RCLT_UDL, CELL_MERGE_HORIZONTAL);		
		return false;
	}
#endif //__STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
	///End FLAT_SHEET_IMPROVEMENT

	/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH		
	bool	applyThemeToResultCurveTable(TreeNode& trOp)
	{
		if( IsOutputSeparateResidualCurveSheet(trOp) )
		{
			DataRange drFlatOut;	
			GetOutput(drFlatOut, GetOutputSlot(0, true, OUTPUT_FLAT_RESULT_SHEET));
	
			Worksheet wks;
			if( drFlatOut ) /// Iris 4/28/2015 ORG-12969-P1 ADD_WARINING_MSG_WHEN_OUTPUT_RESULT_TO_SOURCE_SHEET
				drFlatOut.GetParent(wks);
			
			if( wks )
				return theme_set_label_merge(wks, RCLT_UDL, CELL_MERGE_HORIZONTAL);		
		}
		return false;
	}
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
	///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX

	// virtual 
	// fisher 11/19/2007 ADD_MAP_ID_TO_CHM
	int GetHelpID()
	{
		Tree trOp;
		GetTree(trOp);
		
		return GetOptionIndex(trOp.GUI)>0 ? IDD_XF_DescStats_1 : IDD_XF_DescStats;
	}

	/**
		Construct tree used when computing descriptive statistics.
	*/
	//virtual 
	BOOL Construct(TreeNode& trOperation, int nOption = 0)
	{
		if( WksReportOperation::Construct(trOperation, nOption) )
		{
			//--- CPY 5/6/04 QA70-6367 HISTOGRAM_GRAPHS
			TreeNode trOut = trOperation.Calculation; // Calculation node should have already been prepared in base class
			trOut.Statistics.ID = IDST_DESC_STATS_RESULTS;
			
			///Iris 01/20/05 CLEANUP_CONSTRUCT_ADD_GRAPH
			//ConstructAddGraph(trOperation);
			//ConstructAddGraph(trOperation, 1);//----- CPY 11/3/04	QA70-7122 ADD_BOX_CHART_TO_DESC_STATS
			///end CLEANUP_CONSTRUCT_ADD_GRAPH

			//trOut.BinWks.ID = IDST_BIN_WKS;	///Iris 11/10/04, move into StatsOpBase.h
			//---
			///Iris 01/20/05 CONSTRUCT_GUI_CLEANUP
			//TreeNode		trGUI = ConstructGUI();
			TreeNode		trGUI = ConstructAddGUI(trOperation);
			///end CONSTRUCT_GUI_CLEANUP
			ConstructDescStatGUITree(trGUI, nOption);
			
			bool	bStatsOnRows = nOption > 0? true : false;
			///Iris 4/06/05 INIT_GRAPH_NUMBER
			//----- CPY 11/3/04	QA70-7122 ADD_BOX_CHART_TO_DESC_STATS	
			//ConstructAddReportCommon(trGUI, REPORT_GRAPHS, IDST_REPORT_OPTIONS_DESC_STATS);
			//ConstructAddReportCommon(trGUI, REPORT_GRAPHS | REPORT_2ND_GRAPHS, IDST_REPORT_OPTIONS_DESC_STATS); ///Iris 01/19/05 ADD_GRAPHNUM_OPTION_TO_CONSTRUCT_REPORT
			//ConstructAddReportCommon(trOperation, 0, IDST_REPORT_OPTIONS_DESC_STATS, true, 2);
			DWORD 	dwOptions = bStatsOnRows? 0 : REPORT_ARRANGE_GRAPHS_TO_COLS | REPORT_PLOT_ALL_PLOTS_IN_ONE_GRAPH;
			///Sophy 5/25/2012 ORG-5805 DATASET_IDENTIFIER_MORE_WORK_ON_ANOVA_TOOLS
			if ( bStatsOnRows )
				dwOptions |= REPORT_NO_DATASET_IDENTIFIER;
			///------ Folger 06/01/2012 ORG-5592-S1 SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
			else
				dwOptions |= REPORT_DATASET_IDENTIFIER_OUTPUT_FLAT_SHEET_DEFAULT_ON;
			///------ End SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
			///end DATASET_IDENTIFIER_MORE_WORK_ON_ANOVA_TOOLS
			ConstructAddReportCommon(trOperation, dwOptions, IDST_REPORT_OPTIONS_DESC_STATS, true);
			//-----	
			
			/// Damon 7/24/2013 ORG-8473-S4 v9.100148c PLOT_IN_ONE_CHECKED_BY_DEFAULT
			/// Damon 8/20/2013 ORG-9265-P1 FIX_GUI_FOR_STATS_ON_ROWS
			//PlotInOneChecked(trOperation, true);
			/// END FIX_GUI_FOR_STATS_ON_ROWS
			if(!bStatsOnRows)
				PlotInOneChecked(trOperation, true);
			/// END PLOT_IN_ONE_CHECKED_BY_DEFAULT
			
#ifdef OP_DLG_TOTALLY_NEW_STRUCTURE
			if(!bStatsOnRows)
				ConstructAddReportGraphsOptions(trOperation, dwOptions);
#endif
			
			FilterStatsGUI(trOperation);    ///Jim 01/17/06 v8.0358 CREATE_PLOTS_BRANCH_IN_MAIN_NODES
			
			if(bStatsOnRows)
			{
				/// Iris 4/18/2007 v8.0603 ADD_OUTPUT_DEST_COL_OPTION_STATS_ON_ROWS				
				TreeNode trLog = trGUI.Output.Report.AddReportToResultsLog;
				if(trLog)
				{
					TreeNode trCol = trGUI.Output.Report.InsertNode(trLog, "Column");				
					trCol.DataID = IDE_REPORT_COLUMN;
					trCol.SetAttribute(STR_LABEL_ATTRIB, _L("Column"));	
					string 	strCombo = STR_NEW + "|" + STR_NEXT_TO_SOURCE;
					trCol.SetAttribute(STR_COMBO_ATTRIB, strCombo);
					trCol.strVal = STR_NEW;				
				}
				///END ADD_OUTPUT_DEST_COL_OPTION_STATS_ON_ROWS
				
				//--- Iris 11/03/06 NO_NEED_PLOTS_FOR_STATS_ON_ROWS, from Max's suggestion
#ifndef OP_DLG_TOTALLY_NEW_STRUCTURE
				if(trGUI.Plots)
					trGUI.Plots.Show = false;
				//---
				
				///Arvin 11/09/06 NO_NEED_OPTIONAL_REPORT_TABLES_FOR_STATS_ON_ROWS, from Max's suggestion
				if(trGUI.Output.Create)
				{
					trGUI.Output.Create.Show = false;
					
					///------ Tony 09/08/2017 ORG-10099-P2 SET_WKS_LABEL_EDIT_CONTROL_TO_MAKE_GOOD_SIZE
					if(trGUI.Output.Report)
					{
						int nAttribute;
						trGUI.Output.Report.GetAttribute(STR_ATTRIB_BRANCH, nAttribute);
						nAttribute |= GETNBRANCH_OPEN;
						trGUI.Output.Report.SetAttribute(STR_ATTRIB_BRANCH, nAttribute);
					}
					///------ End SET_WKS_LABEL_EDIT_CONTROL_TO_MAKE_GOOD_SIZE
				}
				///end NO_NEED_OPTIONAL_REPORT_TABLES_FOR_STATS_ON_ROWS
				
#else //OP_DLG_TOTALLY_NEW_STRUCTURE
				OP_GUI_OUTPUT_TABLES_BRANCH(trGUI).Notes.Show = false;
				OP_GUI_OUTPUT_TABLES_BRANCH(trGUI).InputData.Show = false;
				OP_GUI_OUTPUT_TABLES_BRANCH(trGUI).MaskedData.Show = false;
				OP_GUI_OUTPUT_TABLES_BRANCH(trGUI).MissingData.Show = false;
				
				for(int nGraphIndex = 0; nGraphIndex < ConstructGraphNumber(); nGraphIndex++)
				{
					TreeNode trGraph = GetGUIGraphNodes(trOperation, nGraphIndex);
					if( trGraph && trGraph.Show )
						trGraph.Show = false;
				}
#endif //OP_DLG_TOTALLY_NEW_STRUCTURE

				///------ Folger 05/16/2012 ORG-5592-S3 ADD_DATA_IDENTIFIER_FOR_STATS_TOOLS
				///Sophy 5/25/2012 ORG-5805 DATASET_IDENTIFIER_MORE_WORK_ON_ANOVA_TOOLS
				//if ( bStatsOnRows )
				//{
					//check_remove_data_identifier_branch(trGUI);
				//}
				///end DATASET_IDENTIFIER_MORE_WORK_ON_ANOVA_TOOLS
				///------ End ADD_DATA_IDENTIFIER_FOR_STATS_TOOLS
			}
			///Cheney 2007-8-31 QA70-10330 CLEAN_UP_PLOT_SETTING_BRANCH_IN_OUTPUT_RESULT_NODE
			else
			{
				/// Sophy 5/08/2008 FIX_BUG_REPORT_BOOK_BLANK_WHEN_NO_DATUM_SELECTED_IN_STATS_ON_COLUMN
				//GETN_SET_EVENT_EX_HANDLER(trGUI.InputData, _on_input_data_change); //move to descstats_event1			
				/// End FIX_BUG_REPORT_BOOK_BLANK_WHEN_NO_DATUM_SELECTED_IN_STATS_ON_COLUMN
				///Sophy 1/23/2009 v8.0964b CLEAN_UP_PLOT_SETTING_BRANCH_IN_OUTPUT_RESULT_NODE
				//trGUI.Output.PasteResultTable.Show = false;
				/// Iris 10/29/2009 QA81-14546 OP_DLG_NEW_STRUCTURE
				//TreeNode trPasteResultTable = trGUI.Output.PlotSettings.PasteResultTable;
				TreeNode trPasteResultTable = OP_GUI_GRAPH_ARRANGEMENT_NODE(trGUI).PasteResultTable;
				///end OP_DLG_NEW_STRUCTURE
				if ( trPasteResultTable )
					trPasteResultTable.Show = false;
				///end CLEAN_UP_PLOT_SETTING_BRANCH_IN_OUTPUT_RESULT_NODE
				
				/// Iris 10/29/2009 QA81-14546 OP_DLG_NEW_STRUCTURE
				//trGUI.Output.PlotSettings.GraphNumCols.nVal = 0; //to tell this value whether from theme or not 
				OP_GUI_GRAPH_ARRANGEMENT_NODE(trGUI).GraphNumCols.nVal = 0; 
				///end OP_DLG_NEW_STRUCTURE
				
				/// Iris 3/18/2011 ORG-2427 STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT
#ifdef __STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
				TreeNode trFlatReport = trGUI.Output.InsertNode(trGUI.Output.FirstNode, "FlatReport");
				trFlatReport.SetAttribute(STR_LABEL_ATTRIB, _L("Report to Flat Sheet"));
				trFlatReport.ID = TRGP_CHECK;
				trFlatReport.DataID = IDE_STATS_FLAT_SHEET;
				trFlatReport.nVal = 0;
				trFlatReport.SetAttribute(STR_ATTRIB_HANDLER_RC, (ODWP)(PEVENT_NODE_FUNC)report_to_flat_sheet_check_event);
#endif //__STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
				///End STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT
				
				/// Iris 8/22/2011 ORG-2427-S4 STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
				/// Iris 3/26/2015 ORG-12836-S3 IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI				
				/*
				if( trGUI.Output.Report.AddReportToResultsLog )
					trGUI.Output.Report.AddReportToResultsLog.Remove();
				if( trGUI.Output.Report.DumpScriptWindow )
					trGUI.Output.Report.DumpScriptWindow.Remove();
				if( trGUI.Output.Report.DumpNotesWindow )
					trGUI.Output.Report.DumpNotesWindow.Remove();
				*/
				///End IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
				
				TreeNode trFlatBranchTemp;
				GETN_TREE(trFlatTemp)
				/// Iris 8/26/2011 ORG-2427 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX_EX
				//GETN_BEGIN_BRANCH(FlatOut, _L("Report Quantities to Flat Sheet")) GETN_ID_BRANCH(IDE_FLAT_REPORT) GETN_CHECKBOX_BRANCH(1)
				GETN_BEGIN_BRANCH(FlatOut, _L("Quantities")) GETN_ID_BRANCH(IDE_FLAT_REPORT)
				///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX_EX
					construct_report_book_sheet_nodes(_tmpSubNode);
					
					trFlatBranchTemp = trFlatTemp.FlatOut;
					// book
					trFlatBranchTemp.Book.DataID = IDE_FLAT_REPORT_BOOK;
					trFlatBranchTemp.BookName.DataID = IDE_FLAT_REPORT_BOOK_NAME;
					TreeNode trNameForNew = trFlatBranchTemp.BookName.NextNode;
					if( trNameForNew )
						trNameForNew.DataID = IDE_FLAT_REPORT_BOOK_OLD_NAME;
					
					// sheet
					trFlatBranchTemp.Sheet.DataID = IDE_FLAT_REPORT_SHEET;
					trFlatBranchTemp.SheetName.DataID = IDE_FLAT_REPORT_SHEET_NAME;
					trNameForNew = trFlatBranchTemp.SheetName.NextNode;
					if( trNameForNew )
						trNameForNew.DataID = IDE_FLAT_REPORT_SHEET_OLD_NAME;					
				
					/// Iris 3/26/2015 ORG-12836-S3 IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
					//GETN_CHECK(AddReportToResultsLog, _L("Results Log"), false) GETN_ID(IDE_FLAT_REPORT_ADD_TO_RESULTS_LOG)
					//GETN_CHECK(DumpScriptWindow, _L("Script Window"), false) GETN_ID(IDE_FLAT_REPORT_DUMP_SCRIPTWIN)
					//GETN_STR(DumpNotesWindow, _L("Notes Window"), STR_NONE) GETN_ID(IDE_FLAT_REPORT_DUMP_NOTESWIN)
					///End IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
				GETN_END_BRANCH(FlatOut)
				
				/// Iris 3/26/2015 ORG-12836-S3 IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
				//TreeNode trReportTable = trGUI.Output.Report;				
				TreeNode trReportTable = trGUI.Output.Create;
				///End IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
				TreeNode trFlatOut = trGUI.Output.InsertNode(trReportTable, "tmp");
				trFlatOut.Replace( trFlatBranchTemp.Clone(), true, false, false);
				trFlatOut.SetAttribute(STR_OPERATION_OUTPUT_WND_TYPE, EXIST_WKS);
				
#endif // __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
				///End STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
			}
			///end CLEAN_UP_PLOT_SETTING_BRANCH_IN_OUTPUT_RESULT_NODE
			
			///Cheney 2007-5-14 NOT_SUPPORT_SEP_REPORT_IN_STATS_ON_COL	
			//if(bStatsOnRows) // stats on Rows
				//tree_output_branch_mode(trGUI, MDOUT_DISABLE_COMBO);
			//else
				//tree_output_branch_mode(trGUI);
			tree_output_branch_mode(trGUI, MDOUT_DISABLE_COMBO);
			///end NOT_SUPPORT_SEP_REPORT_IN_STATS_ON_COL

			Operation::ConstructAddCommonBottom(trGUI);
			
			return TRUE;
		}

		return FALSE;
	}
	
	/// Iris 3/27/2015 ORG-12835-S1 SUPPORT_TABBED_DLG_FOR_OPERATION_BASED_TOOLS
	// virtual 
	bool IsTabViewMode() { return OC_TOOLS_USING_TAB_MODE; }	
	///End SUPPORT_TABBED_DLG_FOR_OPERATION_BASED_TOOLS
	
	/// Iris 09/11/2014 ORG-11749-S1 ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS
	//virtual
	bool IsReplaceGroupCtrlWithMultiColsCtrl() { return true; }
	/// End ADD_MULTI_COLS_GROUP_CTRL_FOR_EXISTED_TOOLS	
	
	virtual bool IsCreateOneReportDataTableForAllPlotTypes() { return true; }
	//virtual
	void	FilterStatsGUI(TreeNode& trOp) 
	{
		StatsOpBase::FilterStatsGUI(trOp);
		
		//If the tool is Statistics On Rows
		TreeNode trStatsOnRows = trOp.GUI.StatsOnRows;
		if(trStatsOnRows && 1== trStatsOnRows.nVal)
		{
			///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
			//vector<int> vnNodesToHide = {IDE_NUM_MISSING,IDE_VARIANCE,IDE_SKEWNESS,IDE_KURTOSIS,IDE_UNCORSUMSQ,IDE_CORSUMSQ,IDE_COV,
						//IDE_MAD,IDE_SD_X_2,IDE_SD_X_3,IDE_GEO_MEAN,IDE_GEO_SD,IDE_MODE,IDE_WEIGHTSUM,
						//IDE_IMIN,IDE_IMIN,IDE_IMAX,IDE_IQR,IDE_RANGE,IDE_USE_CUSTOM_PERCENTILES,IDE_CUSTOM_PERCENTILES};
			vector<int> vnNodesToHide = {IDE_WEIGHTSUM}
			///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID			
			tree_set_attributes(trOp.GUI, vnNodesToHide, "0");
			
		}	
		///Sophy 12/17/2008 v8.0987d  QA80-12784 ADD_BINNING_CONTROL_FOR_HISTOGRAM_PLOT_IN_STATS_TOOLS add for stats tool(stats column, normality test
		else
		{
			AddHistogramPlotConfigBranch(trOp, trOp.GUI.Output);
		}
		///end ADD_BINNING_CONTROL_FOR_HISTOGRAM_PLOT_IN_STATS_TOOLS
	}
	
	//virtual
	bool SourceRowIndicesNeeded()
	{
		return true;
	}
	
	///Iris 4/06/05 INIT_GRAPH_NUMBER
	//virtual
	int ConstructGraphNumber()
	{
		return 2;
	}
	
	//virtual 
	bool IsEnableInsertResultColumnsToSourceData(int nOption)
	{
		if(nOption > 0)
			return true;
		
		return false;
	}
	
	/// Iris 3/18/2011 ORG-2427 STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT
#ifdef __STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
	// virtual
	bool IsReportHierarchySheet(TreeNode& trGUI)
	{
		TreeNode trFlatReport = trGUI.Output.FlatReport;
		if( trFlatReport && trFlatReport.nVal )
			return false;
		return true;
	}
#endif //__STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
	///End STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT
	
	//virtual 
	PEVENT_GETN GetNewEventFunction()
	{
		return descstats_event1;
	}
	//virtual 
	int	GetOptionIndex(const TreeNode& trGUI)
	{
		return trGUI.StatsOnRows.nVal;
	}
	
	/// Hong 11/19/08 QA80-12558 V8.90875 DESC_STATS_ON_COL_SUPPORT_DATA_FROM_GRAPH
	//virtual
	BOOL	SetInfoFromXF(int nOption, LPCSTR lpcszClass, StringArray &saOptions, StringArray &saNames, LPCSTR lpcszStr2 = NULL)
	{
		Tree trOp;
		GetTree(trOp);
		
		TreeNode		trSpec = tree_check_get_node(trOp, "SpecInfo");
		string			strClass(lpcszClass);
		trSpec.FitType.nVal = nOption;
		trSpec.ClassName.strVal = strClass;	
			
		trSpec.Options.strVals = saOptions;
		trSpec.Option.nVal = nOption;
		if (0 < saNames.GetSize())
			trSpec.Names.strVals = saNames;
		if (lpcszStr2)
			trSpec.Categ.strVal = lpcszStr2;
		
		SetTree(trOp);
		return TRUE;
	}
	/// end DESC_STATS_ON_COL_SUPPORT_DATA_FROM_GRAPH
	
	// Virtual 
	/// Hong 11/19/08 QA80-12558 V8.90875 DESC_STATS_ON_COL_SUPPORT_DATA_FROM_GRAPH
	//string GetClassName() {return "DescStats";}	
	string GetClassName()
	{
		Tree trOp;
		GetTree(trOp);
		TreeNode		trSpecInfo = tree_check_get_node(trOp, "SpecInfo");
		if ( trSpecInfo && trSpecInfo.ClassName )
			return trSpecInfo.ClassName.strVal;
			
		return STR_OPERATION_CLASS_DESCSTATS;
	}
	/// end DESC_STATS_ON_COL_SUPPORT_DATA_FROM_GRAPH
	
	/// Iris 4/07/2008 ADD_DescStats_OUTPUT_CLASS
	//virtual
	bool	InitOutputGUIManagerPointer(const TreeNode& trGUI)
	{
		if(m_pOutputManager)//already init
			return true;
		
		m_pOutputManager = new DescStatsOutputGUIManager;	
		return (NULL != m_pOutputManager);		
	}
	///end ADD_DescStats_OUTPUT_CLASS
	
	/// Iris 5/29/2008 STATS_ON_ROWS_2ND_REPORT_WILL_RESIZE_RESULT_COLS
	//virtual
	bool	IsAutoSizeReport(const TreeNode& trGUI)
	{
		int nOption = GetOptionIndex(trGUI);
		if( nOption > 0 )//on rows
			return false;
		else
			return StatsOpBase::IsAutoSizeReport(trGUI);
	}
	///end STATS_ON_ROWS_2ND_REPORT_WILL_RESIZE_RESULT_COLS
	
	/// Iris 7/11/06 QA70-6367-P5 DIFF_RESULT_SHEET_NAME_FOR_COLS_AND_ROWS
	// virtual
	/// Iris 3/21/2008 v8.0829 QA80-10934 ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME, want GUI tree as input in DescStats::GetResultSheetName
	//string 			GetResultSheetName()
	string 			GetResultSheetName(TreeNode& trGUI)
	///end ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
	{
		/// Iris 3/21/2008 v8.0829 QA80-10934 ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
		//Tree trOp;
		//GetTree(trOp);
		///end ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
		
		string	strSheetName = GetClassName();
		/// Iris 3/21/2008 v8.0829 QA80-10934 ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
		//int nOption = GetOptionIndex(trOp.GUI);
		int nOption = GetOptionIndex(trGUI);
		///end ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
		
		if(nOption > 0) //on Rows
			strSheetName += "OnRows1";
		else
			strSheetName += "OnCols1";
		return strSheetName;
	}
	///end DIFF_RESULT_SHEET_NAME_FOR_COLS_AND_ROWS
	
	/// Iris 3/21/2008 v8.0829 QA80-10934 ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
	//virtual 
	string GetResultBookName(TreeNode& trGUI)
	{
		string strBookName;
		int nOption = GetOptionIndex(trGUI);
		if(nOption > 0) //on Rows
			strBookName = "Row";
		else
			strBookName = "Col";
		strBookName += "Stat1";
		return strBookName;
	}
	///end ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME

	//----- CPY 9/30/07 FIX_CHENEY_MODIFY_TITLE_AS_MAX_SAID
	//virtual
	string GetAnalysisName(int nOption)
	{
		string str = _L("Statistics");
		if(nOption < 0) // short form
			return  str;
		//----- CPY 10/24/07 LOCALIZATION_CLEAN_UP_ON_OPERATION_CODES
		/*
		else if( nOption > 0 )
			return str + " " + _L("on Rows");

		return str + " " + _L("on Columns");
		*/
		if( nOption > 0 )
			return _L("Statistics on Rows");

		return _L("Statistics on Columns");
		//----- end LOCALIZATION_CLEAN_UP_ON_OPERATION_CODES
	}
	//-----
	//virtual 
	string GetDlgDescription(int nOption)
	{
		///Cheney 2007-9-28 MODIFY_TITLE_AS_MAX_SAID
		//string str = "Statistics";
		//
		//if(nOption < 0) // short form
			//return  str;
		//else if( nOption > 0 )
			//return str + " on Rows";
		//
		//return str + " on Columns";
		return _L("Perform Descriptive Statistics");
		///end MODIFY_TITLE_AS_MAX_SAID
	}
	
	/// Iris 10/21/05 CLEANUP_STATS_REPORT_GRAPH_CODES
	/*
	/// YuI 12/07/04 v7.5172 PICTURE_IN_REPORT_IMPROVEMENT
	virtual int	ReportGetPicureIndexFromDataIndex(int nGraphIndex, int nDataIndex)
	{
		switch( ReportGetPlotTypeFromGraphIndex(nGraphIndex) )
		{
		case IDM_PLOT_HISTOGRAM_TYPE:
			return nDataIndex;
			
		case IDM_PLOT_BOX:
			//return 0; //box chart is always one picture
			return nDataIndex;    ///Iris 3/22/05 FIX_GROUP_DATA_ONLY_ONE_BOX_CHART
		}
		
		return -1;
	}
	
	virtual int	ReportGetPlotTypeFromGraphIndex(int nGraphIndex)
	{
		switch( nGraphIndex )
		{
		case 0:
			return IDM_PLOT_HISTOGRAM_TYPE;
			
		case 1:
			return IDM_PLOT_BOX;
		}
		
		return -1;
	}
	/// end PICTURE_IN_REPORT_IMPROVEMENT
	*/
	///End CLEANUP_STATS_REPORT_GRAPH_CODES
	
	///Arvin 11/10/07 XOP_NEED_SUPPORT_CHANGE_FUNCTION	
	//Need call this method from oc code, so move it to public session
	//void ClearOutputTables(TreeNode& trOperation)
	//{
		//StatsOpBase::ClearOutputTables(trOperation);
		//
		//if(trOperation.Calculation.ExVals)
			//trOperation.Calculation.ExVals.Reset(true);
	//}
	///end XOP_NEED_SUPPORT_CHANGE_FUNCTION
	
	//virtual
	void UpdateReportingTables(TreeNode &trOperation, int nTotalNumData, int nExeMode)
	{
		WksReportOperation::UpdateReportingTables(trOperation, nTotalNumData, nExeMode);
		
		updateTableStringMain(trOperation);
	
		//UpdateTableString(trOperation.Calculation.ExVals, true, true, atof(GetTableStringMain(false)) );Alex 06/13/06 SET_EXTREME_VALUES_TABLE_OPEN
		/// Iris 01/15/2007 v8.0541 REMOVE_SUB_TABLE_FROM_ANOVE_MISS_MASK_DATA_TABLE
		//remove sub tables from Extreme value table
		//UpdateTableString(trOperation.Calculation.ExVals, true, true, atof(GetTableStringMain(false)),atof(GetTableStringMain(false)));
		TreeNode trTable = trOperation.Calculation.ExVals;
		if(trTable)
		{
			trTable.SetAttribute(TREE_Table, GetTableStringMain(false) );
		}
		///end REMOVE_SUB_TABLE_FROM_ANOVE_MISS_MASK_DATA_TABLE
	}

	//virtual
	/// Iris 11/16/06 CLEAR_OUT_TABLES_BEFORE_CALC_WHEN_DO_CHANGE_PARAMS
	/*
	void OnBeforeCalculations(TreeNode& trOperation)
	{
		StatsOpBase::OnBeforeCalculations(trOperation);
		
		TreeNode trStatistics = trOperation.Calculation.Statistics;
		if( trStatistics.IsValid())
			trStatistics.RemoveChildrenWithPrefix(CALCULATION_PARAMETER_PREFIX);
	}
	*/
	///end CLEAR_OUT_TABLES_BEFORE_CALC_WHEN_DO_CHANGE_PARAMS
	
	int GetNumberAdditionalRowsOrColumnsInHeading(int nNumData, int numFactors)
	{
		// for desc. stats multiple datasets are already in labels, so only factors can provide
		// additional row/column headers:
		return numFactors;
	}
	
	/// ML 7/15/2004	
	///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
	//string		updateTableStringMain(TreeNode &trOperation, LPCSTR lpcszSet = NULL, bool bForInserting = false)
	int			updateTableStringMain(TreeNode &trOperation, int nTableBits = 0, bool bUseInputTableBits = false)
	///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
	{
		///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		//string			strOld;
		int					nTableBitsOld;
		///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		TreeNode		trTable = trOperation.Calculation.Statistics;
		
		if (trTable)
		{
			///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
			//trTable.GetAttribute(TREE_Table, strOld);
			//if (lpcszSet)
			//	trTable.SetAttribute(TREE_Table, lpcszSet);
			trTable.GetAttribute(TREE_Table, nTableBitsOld);
			if (bUseInputTableBits)
			{
				trTable.SetAttribute(TREE_Table, nTableBits);
				///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
				if ( GetDataRules(trOperation) & DRR_BY_ROWS )
				{
					for(int ii = 1; ; ii++)
					{
						trTable = trOperation.Calculation.GetNode("Statistics"+ii);
						if(!trTable)
							break;
						trTable.SetAttribute(TREE_Table, nTableBits);
					}
				}
				///End STATS_ON_ROWS_SUPPORT_GROUPING
			}
			///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
			else
			{
				string str;
				///Cheney 2007-5-23 QA70-9805 SPEED_UP_STATISTIC_ON_ROW
				//should add an vector to treenode
				//if ( GetDataRules(trOperation) & DRR_BY_ROWS )
				//{
					////bool bTranspose = bForInserting;
					//bool bTranspose = false;
					//str = GetTableStringMain(bTranspose);
					//if(bForInserting)
					//{
						//uint nn = atoi(str);
						//nn |= GETNBRANCH_ROW1_LABEL_OFFSET;
						//str = ftoa(nn);
					//}
				//}
				//else
				///end SPEED_UP_STATISTIC_ON_ROW
				{
					/// Iris 9/12/06 REMOVE_COL_HEADER_FROM_RESULT_TABLE
					/*
					//---- CPY 12/17/04 test allowing user to plot stats results
					//str = GetTableStringMain(true);
					///Echo 1/31/05 OUTPUT_TABLE_TRANSPOSE
					//str = GetTableStringMain(false, true);
					str = GetTableStringMain(true, true);
					///end OUTPUT_TABLE_TRANSPOSE
					//----
					*/
					//--- Iris 06/05/2007 v8.0633 not transpose table on Easwar's suggestion
					//str = GetTableStringMain(true, false);
					if ( GetDataRules(trOperation) & DRR_BY_ROWS )
					{
						///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
						//str = GetTableStringMain(true, false);
						nTableBits = GetTableStringMain(true, false);
						///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
					}
					else
					{
						///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
						//str = GetTableStringMain(false, false);
						nTableBits = GetTableStringMain(false, false);
						///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
						/// Iris 07/08/2011 ORG-2427-S2 IMPROVE_DATA_COLUMN_IN_FLAT_REPORT_SHEET
#ifdef __STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
						if( !IsReportHierarchySheet(trOperation.GUI) )
						{
							nTableBits |= GETNBRANCH_CHANGE_LABEL_TYPES_IN_FLAT; // add this bit to TreeTable attribute to let User Param work
						}
#endif //__STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__

						/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
						TreeNode trFlatOut = trOperation.ResidualCurves.FlatOut;
						if( trFlatOut && !trFlatOut.IsEmpty() )
						{
							int nFlatOutBits = nTableBits | GETNBRANCH_CHANGE_LABEL_TYPES_IN_FLAT; // add this bit to TreeTable attribute to let User Param work
							trFlatOut.SetAttribute(TREE_Table, nFlatOutBits);		
							
							/// Iris 10/11/2011 ORG-4047-P1 CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
							if( trFlatOut.FirstNode )
							{
								trFlatOut.FirstNode.SetAttribute(TREE_Table, GetTableStringDatasets());
							}
							///End CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
						}
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
						///End IMPROVE_DATA_COLUMN_IN_FLAT_REPORT_SHEET
					}
					//--- 
					///end REMOVE_COL_HEADER_FROM_RESULT_TABLE
				}
				
				///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
				//trTable.SetAttribute(TREE_Table, str);
				trTable.SetAttribute(TREE_Table, nTableBits);
				///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
				///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
				if ( GetDataRules(trOperation) & DRR_BY_ROWS )
				{
					for(int ii = 1; ; ii++)
					{
						trTable = trOperation.Calculation.GetNode("Statistics"+ii);
						if(!trTable)
							break;
						trTable.SetAttribute(TREE_Table, nTableBits);
					}
				}
				///End STATS_ON_ROWS_SUPPORT_GROUPING
			}
		}
		else
			error_report("Desc Stats found invalid Calculation.Statistics node");			
			
		///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		//return strOld;
		return nTableBitsOld;
		///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
	}
	/// end ML 7/15/2004	

	
	//virtual
	bool UpdateInsertedColumns(TreeNode& trOp, const DataRange& rngInput, int nDataIndex, int nTotalNumData, DataRange& rngOutput, int nOutputOption)
	{
		int r1, c1, r2, c2;
		Worksheet wksFirst;
		int nWksCount = find_input_range_bounding_box(rngInput, r1, c1, r2, c2, wksFirst,"X");
		if(nWksCount != 1)
			return error_report("Desc Stats only support all input data from the same worksheet");
		
		/// Iris 4/18/2007 v8.0603 ADD_OUTPUT_DEST_COL_OPTION_STATS_ON_ROWS
		if(trOp.GUI.StatsOnRows.nVal > 0) //stats on rows
		{
			TreeNode 	trOutCol = trOp.GUI.Output.Report.Column;
			if( trOutCol && PDS_NEW == str_to_predefined_type(trOutCol.strVal) )
			{
				c2 = -1;
			}
		}
		///end ADD_OUTPUT_DEST_COL_OPTION_STATS_ON_ROWS
		
		//---- Iris 10/30/06 STATS_ON_ROWS_FAIL_TO_REPORT_INTP_SOURCE
		if(c2<0)
			c2 = wksFirst.Columns.Count()-1;
		//----
		
		///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		//string	strCache = updateTableStringMain(trOp, NULL, true);
		int nCache = updateTableStringMain(trOp);
		///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		/// Iris 9/17/05 QA70-8015-P15 OUTPUT_RESULT_CURVE_TO_WKS
		//bool	bOK = InsertReportToSourceWks(trOp, trOp.Calculation.Statistics, wksFirst, c2 + 1, rngOutput);
		bool	bOK = InsertReportToWks(trOp, trOp.Calculation.Statistics, wksFirst, c2 + 1, rngOutput);
		///End OUTPUT_RESULT_CURVE_TO_WKS
		///Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		//updateTableStringMain(trOp, strCache, true);
		updateTableStringMain(trOp, nCache, true);
		///End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		///Arvin 11/09/06 ADD_COMMENTS_TO_STATSONROWS_RESULT_COLUMNS
		if(rngOutput)
		{
			//---- CPY 10/24/07 OPERATION_CLASS_USING_LOCALIZATION_DLL
			//string strName;
			//strName = "Statistics On Rows of " + rngInput.GetDescription();
			string strName = "Err: str not in oErrMsg";
			ocu_load_msg_str(IDS_STATS_ON_ROWS_OF, strName, rngInput.GetDescription());
			//----
			SetOuputColComments(rngOutput, strName);
		}
		///end ADD_COMMENTS_TO_STATSONROWS_RESULT_COLUMNS
		return bOK;
	}
	///Arvin 11/07/06 STATS_ON_ROW_OUTPUT_RESULTS_TO_SHEET
	/*
	bool PrepareOutputSheet(Datasheet& wksMatLayer, Worksheet& wksInputFirstRange, TreeNode& trOperation, bool& bNewBookCreated, LPCSTR lpcszDefaultSheetName, LPCSTR lpcszDefaultBookName)
	{
		string strReportBook;
		int nSpecialType = PDS_NEW, nSheetSpecialType = PDS_NEW;
		if(wksInputFirstRange)
		{
			strReportBook = GetReportOutputBookName(trOperation.GUI, &nSpecialType);
			bNewBookCreated = (PDS_NEW == nSpecialType && strReportBook.IsEmpty())? true:false;			
		}
		else
			bNewBookCreated = true;
		string strReportSheet = GetReportOutputSheetName(trOperation.GUI, &nSheetSpecialType);
		Page		pg;
		if(wksMatLayer.IsValid())
		{
			wksMatLayer.GetParent(pg);
			bNewBookCreated = false;
		}
		if(!pg)
			pg = Project.Pages(strReportBook);
	
		if( !pg )
		{
			if(PDS_SOURCE == nSpecialType && FALSE == bNewBookCreated) // auto
			{
				wksInputFirstRange.GetParent(pg);
				if( !pg )
					return error_report("PrepareOutput found no workbook to be used");
			}
			else
			{
				bNewBookCreated = true;		
				WorksheetPage wp;
				wp.Create(NULL, CREATE_HIDDEN);
				pg = wp;
	
				if(strReportBook.IsEmpty())
					strReportBook = lpcszDefaultBookName;
					
				if(!strReportBook.IsEmpty())
				{
					pg.SetLongName(strReportBook, false);
					pg.TitleShow = WIN_TITLE_SHOW_BOTH;
				}
			}
		}
	
		if(!strReportSheet.IsEmpty())
		{
			wksMatLayer = pg.Layers(strReportSheet);
			if(wksMatLayer)
				return true; 
		}
		else 
		{
			strReportSheet = lpcszDefaultSheetName;
		}

		int nn = pg.AddLayer(strReportSheet);
		wksMatLayer = pg.Layers(nn);
	
		if( TRUE == bNewBookCreated && nn > 0) 
		{
			Layer layJunk = pg.Layers(0);
			layJunk.Destroy();
		}
		if(wksMatLayer.GetNumCols() > 0)
		{
			wksMatLayer.SetNumRows(0);
		}
		
		return true;
	}
	bool GetDescStatsInputRangeString(const DataRange& rngInput, string& strRange)
	{
		int c1, c2, r1, r2;
		Worksheet wksInput;
		int nWksCount = find_input_range_bounding_box(rngInput, r1, c1, r2, c2, wksInput,"X");
		if(nWksCount != 1)
			return error_report("Desc Stats only support all input data from the same worksheet");
		
		Column col1(wksInput, c1);
		Column col2(wksInput, c2);
		string strInput, strEnd; 
		col1.GetRangeString(strInput);
		strEnd = col2.GetLongName();
		if(strEnd.IsEmpty())
			strEnd = col2.GetName();
		strInput.Replace("Col", "");
		strInput.Remove('(');
		strInput.Remove(')');
		strRange = "StatsOnRows of " + strInput + ":" + strEnd;
		return true;
	}
	*/
	bool SetOuputColComments(const DataRange& rngOutput, string& strComments)
	{
		int numRange = rngOutput.GetNumRanges();
		if(numRange < 0)
			return false;
		for( int ii = 0; ii < numRange; ii++)
		{
			Worksheet sourceWks;
			string strRange;
			int r1, r2, c1, c2;
			rngOutput.GetRange(ii, r1, c1, r2, c2, sourceWks, &strRange);
			for(int jj = c1; jj <= c2; jj++)
				sourceWks.Columns(jj).SetComments(strComments);
		}
		return true;
	}
	
	///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
	int CheckGetUDLType(vector<string>& vsUDLNames, LPCSTR lpczUDL)
	{
		int nFind = vsUDLNames.Find(lpczUDL);
		if(nFind < 0)
			nFind = vsUDLNames.Add(lpczUDL);
		if(nFind < 0)
			return -1;
		else
			return nFind + RCLT_UDL;
	}
	
	bool PrepareOuputColLabels(TreeNode& trOp, DataRange& drInput, DataRange& drOutput, vector<int>& vnLabelTypes, vector<int>& vnJunkLabels)
	{
		Worksheet wksOut;
		int r1, r2, c1, c2;
		drOutput.GetRange(0, r1, c1, r2, c2, wksOut);
		if(!wksOut)
			return false;
		vnLabelTypes.SetSize(0); 
		vnJunkLabels.SetSize(0); 
		
		Grid gg;
        gg.Attach(wksOut);  
        vector<string> vsUDLNames;
        gg.GetUserDefinedLabelNames(vsUDLNames);
        int nUDLNames = vsUDLNames.GetSize();
		
        ///------ Tony 07/27/2017 ORG-10099-S1 STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
        bool bOutputWksSameAsInput = false;
        ///------ End STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
        
        int nSrcTxtLabel = -1, nQuantitiesLabel = -1;
		TreeNode trGroup = trOp.GUI.InputData.Range1.F;
		if(trGroup && !trGroup.strVal.IsEmpty() && !compare_string_localization(trGroup.strVal, STR_OPTIONAL))
		{			
			PFN_GET_LABEL_NAME_BY_TYPE pfn_get_label_name_by_type = NULL;
			
			int nRanges = drInput.GetNumRanges();
			Worksheet wks;
			string strRange;
			for(int ii = 0; ii < nRanges; ii++)
			{
				if(!drInput.GetRange(ii, r1, c1, r2, c2, wks, &strRange) || strRange.CompareNoCase("F") != 0)
					continue;
				
				 ///------ Tony 07/27/2017 ORG-10099-S1 STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
				bOutputWksSameAsInput = is_same_layer(wks, wksOut);
				///------ End STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END

				int nLabel = wks.GetLabelType(r1);
				switch(nLabel)
				{
				case RCLT_LONG_NAME:	//If Long Name is selected for Group, we need to add a User Parameter "Quantities", put the Long Name to this label row
					nQuantitiesLabel = CheckGetUDLType(vsUDLNames, "Quantities");
					vnLabelTypes.Add(nLabel);
					break;
				case RCLT_COMMENT:		//If Comments is selected for Group, we need to add a User Parameter "Source", put the "Statistics On Rows of XXX" 
					nSrcTxtLabel = CheckGetUDLType(vsUDLNames, "Source");
					vnLabelTypes.Add(nLabel);
					break;
				default:
					if(nLabel >= RCLT_UDL)
					{
						bool bRet = false;
						if( !pfn_get_label_name_by_type )
							pfn_get_label_name_by_type = Project.FindFunction("get_label_name_by_type", "OriginLab\\WksColLabels");
						if( pfn_get_label_name_by_type )
						{
							string strLabel = pfn_get_label_name_by_type(nLabel, wks);
							if( !strLabel.IsEmpty() )
							{
								int nUDLType = CheckGetUDLType(vsUDLNames, strLabel);
								vnLabelTypes.Add(nUDLType);
								bRet = true;
							}
						}
						if(!bRet)
							vnLabelTypes.Add(-1);
					}
					else
						vnLabelTypes.Add(nLabel);
					break;
				}
				
			}	
		}
		
		if(nSrcTxtLabel < 0)
			nSrcTxtLabel = RCLT_COMMENT;
		vnLabelTypes.InsertAt(0, nSrcTxtLabel);
		
		if(nQuantitiesLabel > 0)
			vnLabelTypes.InsertAt(0, nQuantitiesLabel);
		
		if(vsUDLNames.GetSize() != nUDLNames)
			gg.SetUserDefinedLabelNames(vsUDLNames);
		
		vector<int> vnShowLabels;
		gg.GetShowLabels(vnShowLabels);
		
		///------ Tony 07/27/2017 ORG-10099-S1 STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
		int nShowLabelsAdded = 0;
		///------ End STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
		
		vector<uint> vecIndex;		
		for(int ii = 0; ii < vnLabelTypes.GetSize(); ii++)
		{
			if(vnShowLabels.Find(vecIndex, vnLabelTypes[ii]) < 1)
			///------ Tony 07/27/2017 ORG-10099-S1 STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
				//vnShowLabels.InsertAt(0, vnLabelTypes[ii] );	
			{
				vnShowLabels.Add(vnLabelTypes[ii] );
				nShowLabelsAdded ++;
			}
			///------ End STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
		}
		if(vnShowLabels.Find(vecIndex, RCLT_LONG_NAME) < 1)
			vnShowLabels.InsertAt(0, RCLT_LONG_NAME);
		gg.SetShowLabels(vnShowLabels);
		
		///------ Tony 07/27/2017 ORG-10099-S1 STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
		if(trGroup && bOutputWksSameAsInput && nShowLabelsAdded > 0)
		{
			Tree trRange;
			drInput.GetTree(trRange);
			if(trRange.F)
				trGroup.strVal = trRange.F.strVal;
		}
		///------ End STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
		
		if(trGroup)
		{
			string strLabels, strAttrib = "_LabelTypes";
			trGroup.GetAttribute(strAttrib, strLabels);
			
			vector<uint> vecIndex;
			vector<string> vsTemp;
			int nSize = str_separate(strLabels, STR_TOKEN_SEP, vsTemp);
			for(int ii = nSize - 1; ii >= 0; ii--)
			{
				if(vnLabelTypes.Find( vecIndex, atoi(vsTemp[ii]) ) > 0)
					vsTemp.RemoveAt(ii);
			}			
			convert_string_vector_to_int_vector(vsTemp, vnJunkLabels);
			
			if(vnJunkLabels.Find(vecIndex, RCLT_LONG_NAME) > 0)
				vnJunkLabels.RemoveAt(vecIndex[0]);
			if(vnJunkLabels.Find(vecIndex, RCLT_COMMENT) > 0)
				vnJunkLabels.RemoveAt(vecIndex[0]);
			
			convert_int_vector_to_string_vector(vnLabelTypes, vsTemp);
			trGroup.SetAttribute(strAttrib, str_combine(vsTemp, STR_TOKEN_SEP));
		}
		
		return true;
	}
	
	bool SetOuputColLabels(TreeNode& trOp, DataRange& drInput, int nIndex, DataRange& drOutput, const vector<int>& vnLabelTypes, LPCSTR lpczSrc, const vector<int>& vnJunkLabels)
	{	
		int nQuantitiesLabel = -1;
		vector<int> vnLabelTypesTemp;
		vector<uint> vecIndex;
		vnLabelTypesTemp = vnLabelTypes;
		if(vnLabelTypes.Find(vecIndex, RCLT_LONG_NAME) > 0)
		{
			nQuantitiesLabel = vnLabelTypesTemp[0];
			vnLabelTypesTemp.RemoveAt(0);
		}
		
		vector<string> vsFactors;
		DWORD dwRules = GetDataRules(trOp);
		drInput.GetFactorsValues(dwRules, nIndex, &vsFactors);
		vsFactors.InsertAt(0, lpczSrc);
		int nLabels = vsFactors.GetSize();
		if(vnLabelTypesTemp.GetSize() != nLabels)
		{
			ASSERT(0);
			return false;
		}				
		int nJunks = vnJunkLabels.GetSize();
		
		int numRange = drOutput.GetNumRanges();
		for( int nRange = 0; nRange < numRange; nRange++)
		{
			Worksheet wksOut;
			int r1, r2, c1, c2;
			drOutput.GetRange(nRange, r1, c1, r2, c2, wksOut);
			if(c1 < 0)
				break;
			
			for(int jj = c1; jj <= c2; jj++)
			{
				if(nQuantitiesLabel > 0)
				{
					string strQ;
					wksOut.Columns(jj).GetExtendedLabel(strQ, RCLT_LONG_NAME);
					wksOut.Columns(jj).SetExtendedLabel(strQ, nQuantitiesLabel);
					
				}
				
				for(int ii = 0; ii < nLabels; ii++)
				{
					if(vnLabelTypesTemp[ii] > -1)
						wksOut.Columns(jj).SetExtendedLabel(vsFactors[ii], vnLabelTypesTemp[ii]);
				}
				
				for(ii = 0; ii < nJunks; ii++)
				{
					wksOut.Columns(jj).SetExtendedLabel("", vnJunkLabels[ii]);
				}
			}
			
			///------ Tony 08/21/2017 ORG-10099-P2 OUTPUT_COL_AUTO_SIZE
			vector<int> vnLabelTypesAutoSize;
			vnLabelTypesAutoSize = vnLabelTypesTemp;
			if(nQuantitiesLabel > 0)
				vnLabelTypesAutoSize.Add(nQuantitiesLabel);
			///------ Tony 09/08/2017 ORG-10099-P2 SET_WKS_LABEL_EDIT_CONTROL_TO_MAKE_GOOD_SIZE
			for(int nn = 0; nn < vnLabelTypesTemp.GetSize(); nn++)
			{
				wks_set_label_text_control(wksOut, vnLabelTypesTemp[nn], WKS_LABEL_TEXT_CONTROL_EDIT);
			}
			///------ End SET_WKS_LABEL_EDIT_CONTROL_TO_MAKE_GOOD_SIZE
			ORANGE rng;
			rng.r1 = 0;
			rng.c1 = c1;
			rng.r2 = -1;
			rng.c2 = c2;
			///------ Folger 01/10/2019 ORG-19568-S1 ANALYSIS_FLAT_SHEET_REPORT_NO_ADJUST_WIDTH
			//autosize_rowcol(wksOut, 1.5, 25, -1, -1, 0, 0, 0, 0, 0, 0, vnLabelTypesAutoSize, false, true, false, &rng);	
			///------ Folger 10/15/2020 ORG-22621-P1 LIMIT_REPORT_AUTO_SIZE_ROW_HEIGHT
			//autosize_rowcol(wksOut, 1.5, 25, -1, -1, report_autosize_cntrl(wksOut), 0, 0, 0, 0, 0, vnLabelTypesAutoSize, false, true, false, &rng);	
			autosize_rowcol(wksOut, 1.5, 25, -1, okutil_report_autosize_max_row_height(), report_autosize_cntrl(wksOut), 0, 0, 0, 0, 0, vnLabelTypesAutoSize, false, true, false, &rng);	
			///------ End LIMIT_REPORT_AUTO_SIZE_ROW_HEIGHT
			///------ End ANALYSIS_FLAT_SHEET_REPORT_NO_ADJUST_WIDTH
			///------ End OUTPUT_COL_AUTO_SIZE
		}		
		

		return true;
	}
	///End STATS_ON_ROWS_SUPPORT_GROUPING
	
	bool InsertResultToNewSheet(TreeNode& trOp, const DataRange& rngInput, int nDataIndex, int nTotalNumData, int nOutputOption = -1)
	{
		Worksheet	wksInputFirstRange;
		vector<int>	vFactorSizes;
		DWORD dwRules = GetDataRules(trOp);
		int nNumData = rngInput.GetNumData(dwRules, NULL, &wksInputFirstRange, &vFactorSizes);

		bool		bNewBookCreated = false;
		Worksheet	wksOutput;		
		DataRange	rgResultRange;
		Datasheet*	pdsResultSheet;
		pdsResultSheet = &wksOutput;
		bool bHasOutput = GetOutput(rgResultRange, *pdsResultSheet, WksReportOperation::GetOutputSlot(nDataIndex, false, nOutputOption));
		if(!bHasOutput)
		{
			//--------- CPY 1/19/2007 COMPILE_ERR_DESC_STATS
			//if(!PrepareOutput(wksOutput, wksInputFirstRange, trOp, bNewBookCreated, GetResultSheetName(), "Statistics On Rows") )
			///Sophy 5/29/2008 QA80-10934-P10 CORRECT_STATS_ON_ROWS_RESULT_BOOK_NAME moved from private
			//string strBook = _L("Statistics On Rows");
			string strBook = GetResultBookNameFromGUI( trOp.GUI );
			///end CORRECT_STATS_ON_ROWS_RESULT_BOOK_NAME
			/// Iris 3/21/2008 v8.0829 QA80-10934 ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
			//string strSheet = GetResultSheetName();
			///Sophy 5/29/2008 QA80-10934-P10 CORRECT_STATS_ON_ROWS_RESULT_BOOK_NAME
			//string strSheet = GetResultSheetName(trOp.GUI);
			string strSheet = GetResultSheetNameFromGUI( trOp.GUI );
			///end CORRECT_STATS_ON_ROWS_RESULT_BOOK_NAME
			///end ADD_EDITBOX_TO_SPECIFICATION_BOOK_SHEET_NAME
			if(!PrepareOutput(wksOutput, wksInputFirstRange, trOp, bNewBookCreated, strSheet, strBook) )
			//---------
				return error_report("Failed in PrepareOutput");
		}
		else
		{
			///Arvin 08/24/07 SHOULD_NOT_CREATE_NEW_RESULT_SHEET_FOR_AUTO_UPDATE
			//WorksheetPage wksPage = pdsResultSheet->GetPage();	
			//wksOutput.Attach(wksPage.GetName());
			rgResultRange.GetParent(wksOutput);
			///end SHOULD_NOT_CREATE_NEW_RESULT_SHEET_FOR_AUTO_UPDATE
		}
		
		///Arvin 08/31/07 PDS_CUSTOM_CAN_NOT_WORK_IN_STATS_ON_ROWS
		int nStartCol = -1;
		TreeNode 	trOutSheet = trOp.GUI.Output.Report.Sheet;
		if( trOutSheet && PDS_CUSTOM == str_to_predefined_type(trOutSheet.strVal) )
			nStartCol = wksOutput.Columns.Count()-1;
		///end 	PDS_CUSTOM_CAN_NOT_WORK_IN_STATS_ON_ROWS
		
		///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
		//DataRange		rngInsertedColumns;
		/////Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		////string	strCache = updateTableStringMain(trOp, NULL, true);
		//int	nCache = updateTableStringMain(trOp);
		/////End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		/////Arvin 08/31/07 PDS_CUSTOM_CAN_NOT_WORK_IN_STATS_ON_ROWS
		////bool	bOK = InsertReportToWks(trOp, trOp.Calculation.Statistics, wksOutput, 0, rngInsertedColumns);
		//bool	bOK = InsertReportToWks(trOp, trOp.Calculation.Statistics, wksOutput, nStartCol+1, rngInsertedColumns);
		/////end PDS_CUSTOM_CAN_NOT_WORK_IN_STATS_ON_ROWS
		/////Kyle 12/10/2010 ORG-1720-P1 TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		////updateTableStringMain(trOp, strCache, true);
		//updateTableStringMain(trOp, nCache, true);
		/////End TABLE_BITS_USE_UINT_INSTEAD_OF_STRING_TO_PREVENT_DIGITS_LOST
		bool bOK = inserted_columns(trOp, wksOutput, nStartCol, rngInput, nOutputOption);
		///End STATS_ON_ROWS_SUPPORT_GROUPING
		if(!bOK)
			return error_report("Failed in UpdateInsertedColumns");

		///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
		//if(!bHasOutput)
		//{					
			//SetOuputColComments(rngInsertedColumns, strName);
			//SetOutput(rngInsertedColumns, WksReportOperation::GetOutputSlot(nDataIndex, false, nOutputOption));					
		//}
		///End STATS_ON_ROWS_SUPPORT_GROUPING
		
		return true;
	}
	///END STATS_ON_ROW_OUTPUT_RESULTS_TO_SHEET

	///------ Folger 01/21/09 RESET_ALL_GRAPHS_FAILS_TO_PLOT_HISTOGRAM_IN_NLFIT
	/*
	///Arvin 06/19/07 WRONG_HISTOGRAM_AND_BOXCHART_PLOTS_WHILE_DATA_HAVE_FACTORS
	//For statistics on column, StatsTree is used for histogram and boxchart, so we should not
	//remove it after histogram plotting
	bool IsStatsTreeRemovable(TreeNode& trOp, int nGraphIndex)
	{
		if(IsCreateHistogramGraph(trOp) && IsCreateBoxChartGraph(trOp) && nGraphIndex == GRAPH_STATS_HISTOGRAM)
			return false;
		
		return true;
	}
	///end WRONG_HISTOGRAM_AND_BOXCHART_PLOTS_WHILE_DATA_HAVE_FACTORS
	*/
	///------ End RESET_ALL_GRAPHS_FAILS_TO_PLOT_HISTOGRAM_IN_NLFIT
	
	///Arvin 09/03/07 WRONG_WEIGHT_LABEL_IN_MASK_AND_MISSING_DATA_TABLE
	virtual	string	GetMaskedOrMissingDataTableErrorWeightColumnName()
	{
		return WKSH_OPERATION_INFO_DATA_WEIGHT;
	}
	///END WRONG_WEIGHT_LABEL_IN_MASK_AND_MISSING_DATA_TABLE
	
protected:
	///Iris 01/22/05 MOVE_DESCSTATS_TO_BASE_CLASS
	///////////////////////////////////////////////////////////////////////
	////virtual
	//BOOL	CalcOneData(TreeNode &trOp, int index, int nTotalNumData, const vector<int> &vFactorSizes,
						//const vector<string> &vstrFactors, vector &vData, vector &vDummy, matrix &mDummy, vector &vWeights, DWORD dwPlotObjUID, int nRowColIndex)
	//{
//
		//TreeNode			trGUI = trOp.GUI;
		//DescStatResults		stRes;
		//vector				vPercents; // Which percentiles to compute; it should come from settings
		//vector				vPercentiles;
		///// YuI 12/07/04 v7.5172 PICTURE_IN_REPORT_IMPROVEMENT
		//vector<bool>		vShow;
		///// end PICTURE_IN_REPORT_IMPROVEMENT
		//QuantileResults		stQuantiles;
		//
		///// Iris 9/21/04 ADD_DEN_FALG_OPTION
		////if ( stats_descriptive(vData, stRes, &vWeights) == STATS_NO_ERROR && calcOneDataPercentilesAndRange(trGUI, vData, vPercents, vPercentiles, stQuantiles))
		////int 				iDenFlag = trGUI.Computation.VarDivisor.nVal;   /// Iris 12/01/04 MOVE_COMPUTER_CONTROL_INSIDE_QUANTITIES
		////int 				iDenFlag = trGUI.Quantities.Moments.VarDivisor.nVal;
		//int 				iDenFlag = trGUI.Computation.VarDivisor.nVal;   ///Iris 12/20/04 MOVE_TO_COMPCONTROL_BRANCH
		///// YuI 12/07/04 v7.5172 PICTURE_IN_REPORT_IMPROVEMENT
		////	if ( stats_descriptive(vData, stRes, &vWeights, SU_DEFAULT_CONF_LEVEL, iDenFlag) == STATS_NO_ERROR && calcOneDataPercentilesAndRange(trGUI, vData, vPercents, vPercentiles, stQuantiles))
		//if ( stats_descriptive(vData, stRes, &vWeights, SU_DEFAULT_CONF_LEVEL, iDenFlag) == STATS_NO_ERROR && CalcOneDataPercentilesAndRange(trOp, vData, vPercents, vPercentiles, vShow, stQuantiles))
		///// end PICTURE_IN_REPORT_IMPROVEMENT
		//{
			//string			strDataLabel;
			////GetEscapedMainDataString(strDataLabel, index + 1);
			//GetOneDataLabel(trOp, index, nRowColIndex, strDataLabel);
			//
			//TreeNode		trTable = tree_check_get_node(trOp.Calculation, "Statistics", IDST_DESC_STATS_RESULTS);
			//
			//TreeNode		trRow = check_add_enumerated_node(trTable, CALCULATION_PARAMETER_PREFIX, index + 1, IDST_TEMP_ONE_SET, STR_LABEL_ATTRIB, strDataLabel);
			////////////////////
			//// Factor values:
			//tree_add_more_labels(trRow, vstrFactors);
						//
			////////////////////
			//// Main statistics results:
			//trRow += stRes;
//
			//
			////////////////////
			//// Quantiles:
			//trRow += stQuantiles;
			//
			////////////////////
			//// Percentiles:
			///// YuI 12/07/04 v7.5172 PICTURE_IN_REPORT_IMPROVEMENT
			///*
			//string strTemp;
			//for (int iperc = 0; iperc < vPercentiles.GetSize(); iperc++)
			//{
				//strTemp.Format("P%s", ftoa(vPercents[iperc]));
				//TreeNode	trPerc = check_add_enumerated_node(trRow, CALCULATION_PERCENTILE_PREFIX, iperc+1, IDE_CUSTOM_PERCENTILES + iperc, STR_LABEL_ATTRIB, strTemp);
				//trPerc.dVal = vPercentiles[iperc];
			//}
			//*/
			//SetPercentilesToTree(trRow, vPercents, vPercentiles, vShow);
			///// end PICTURE_IN_REPORT_IMPROVEMENT
//
			///// ML 8/17/2004 QA70-6825 RLOG_QUERY
			////trRow.ID = IDST_DESC_STATS_ONE_SET + index;// restore ID, struct assignment will wipe out ID, see struct assignments above
			//trRow.ID = make_one_set_ID(IDST_DESC_STATS_ONE_SET, index);// restore ID, struct assignment will wipe out ID, see struct assignments above
			///// end RLOG_QUERY
//
			////-------- CPY 12/31/04 PICTURE_IN_REPORT_IN_BASE_CLASS
			///*
			/////////////////////////
			//// Histogram graphs			
			////addBinDataAndMakeHistogramGraphs(trOp, index, vData, vstrFactors, strDataLabel);  /// Iris 11/09/04 CENTRALIZE_CODE_INTO_STATSOPBASE_HEADER
			//AddBinDataHistogramGraph(trOp, index, vData, vstrFactors, 0, strDataLabel);
			//
			/////////////////////////
			//// Box Chart
			////addPercentilesAndMakeBoxCharts(trOp, index, vData, vstrFactors, strDataLabel);   /// Iris 11/09/04 CENTRALIZE_CODE_INTO_STATSOPBASE_HEADER
			//AddPercentilesAndMakeBoxCharts(trOp, index, vData, vstrFactors, 1, strDataLabel);
			//*/
			//AddBinDataTableAndGraphNodes(trOp, index, vData, vstrFactors, strDataLabel);
			////-------- end PICTURE_IN_REPORT_IN_BASE_CLASS
			//return TRUE;
		//}
		//return FALSE;
	//}
	//*/
	///------ Folger 10/16/2018 ORG-19032-P3 RANGE_GETDATA_RETURN_COMBINED_GROUP_EXISTED_INFO
	virtual STGETDATAOUTPUTINFO* CalcMultiDataGetDataOutInfo() {return &m_stCalcMultiDataGetDataOutInfo;}
	///------ End RANGE_GETDATA_RETURN_COMBINED_GROUP_EXISTED_INFO
	
	BOOL	CalcOneData(TreeNode &trOp, int index, int nTotalNumData, const vector<int> &vFactorSizes,
						const vector<string> &vstrFactors, vector &vData, vector &vDummy, matrix &mDummy, vector &vWeights, DWORD dwPlotObjUID, int nRowColIndex, const vector<int>& vintRowsInSource = NULL)
	{
		int nDataIndex = index; /// Iris 10/18/2011 ORG-4125-P1 FIX_PLOT_SAME_GRAPH_IN_ONE_GRAPH_FAILED_FOR_MULTI_FACTORS_DATA
		/// Iris 9/22/2011 ORG-3208-S1 FIX_REPORT_GRAPH_ISSUE_FOR_MISSED_FACTOR_IN_MULTI_GROUPS_DATA
		/// Iris 11/22/2011 ORG-4373-P1 KEEP_MISSING_VALUE_FACTOR
		//if( !CheckCorrectDataIndexFromTrimEmptyGroupPair(index, vData) )
		///------ Folger 10/16/2018 ORG-19032-P3 RANGE_GETDATA_RETURN_COMBINED_GROUP_EXISTED_INFO
		//if( vFactorSizes.GetSize() > 1 && !CheckCorrectDataIndexFromTrimEmptyGroupPair(index, vData) )
		if (!CheckCorrectDataIndexFromTrimEmptyGroupPair(index))
		///------ End RANGE_GETDATA_RETURN_COMBINED_GROUP_EXISTED_INFO
			return true;
		///End KEEP_MISSING_VALUE_FACTOR
		///End FIX_REPORT_GRAPH_ISSUE_FOR_MISSED_FACTOR_IN_MULTI_GROUPS_DATA
		///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
		//string			strDataLabel;
		/////Iris 3/22/05 UPDATE_COLUMN_LABEL_FOR_GROUP_DATA
		///// Iris 10/18/2011 ORG-4125-P1 FIX_PLOT_SAME_GRAPH_IN_ONE_GRAPH_FAILED_FOR_MULTI_FACTORS_DATA
		////GetOneDataLabel(trOp, index, nRowColIndex, strDataLabel);
		//GetOneDataLabel(trOp, nDataIndex, nRowColIndex, strDataLabel);
		/////End FIX_PLOT_SAME_GRAPH_IN_ONE_GRAPH_FAILED_FOR_MULTI_FACTORS_DATA
		vector<string>	vsDataLabel;
		GetOneDataLabel(trOp, nDataIndex, nRowColIndex, vsDataLabel);
		///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
		//GetOneDataLabel(trOp, index, nRowColIndex, strDataLabel, vstrFactors);
		///end UPDATE_COLUMN_LABEL_FOR_GROUP_DATA
		bool 			bMultiModes;
		///Arvin 08/14/07 v8.0681 WRONG_MAX_AND_MIN_INDEX_IN_QUANTILES_WHEN_DATA_HAS_FACTORS
		//if( AddDescStatsTable(trOp, index, vData, strDataLabel, vWeights, vstrFactors, true, true, &bMultiModes))
		///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
		//if( AddDescStatsTable(trOp, index, vData, strDataLabel, vWeights, vstrFactors, true, true, &bMultiModes, vintRowsInSource))
		if( AddDescStatsTable(trOp, index, vData, vsDataLabel, vWeights, vstrFactors, true, true, &bMultiModes, vintRowsInSource))
		///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
		///END 	WRONG_MAX_AND_MIN_INDEX_IN_QUANTILES_WHEN_DATA_HAS_FACTORS
		{
			/// Iris 11/22/2011 ORG-4373-P1 KEEP_MISSING_VALUE_FACTOR
			// above CheckCorrectDataIndexFromTrimEmptyGroupPair function already checked the following case, cannot simply remove zero point row from report.
			/*
			/// Iris 07/08/2011 ORG-3208-S1 TO_REMOVE_N_EQUAL_TO_ZERO_ROW
			TreeNode trStatsTable = trOp.Calculation.GetNode(TABLE_DESC_STATS);
			string strRowName = CALCULATION_REPORT_TABLE_COL_PREFIX + (index + 1);
			TreeNode trRow = trStatsTable.GetNode(strRowName);
			ASSERT( trRow.IsValid() );
			if( !trRow.IsValid() )
				return FALSE;
			if( 0 == trRow.N.nVal )
			{
				trRow.Show = false;
			}
			///End TO_REMOVE_N_EQUAL_TO_ZERO_ROW
			*/
			///End KEEP_MISSING_VALUE_FACTOR
			
			/// Iris 3/18/2011 ORG-2427 STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT
#ifdef __STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
			if( !IsReportHierarchySheet(trOp.GUI) )
			{
				/// Iris 07/08/2011 ORG-3208-S1 TO_REMOVE_N_EQUAL_TO_ZERO_ROW
				/*
				TreeNode trStatsTable = trOp.Calculation.GetNode(TABLE_DESC_STATS);
				TreeNode trRow = tree_get_node(trStatsTable, index, ATRN_SKIP_LEAFS);
				ASSERT( trRow.IsValid() );
				*/
				///End TO_REMOVE_N_EQUAL_TO_ZERO_ROW
				trStatsTable.RemoveAttribute(STR_LABEL_ATTRIB); 
				trRow.RemoveAttribute(STR_LABEL_ATTRIB); // remove data label
				
				// add data label treenode, this treenode will display as a column in flat report worksheet
				/// Iris 07/08/2011 ORG-2427-P1 SHOW_GROUP_COLUMN_IN_FLAT_REPORT_SHEET
				/*
				TreeNode trFirstNode = trRow.FirstNode;
				TreeNode trDataLabel = trRow.InsertNode(trFirstNode, "Data");
				*/
				// add factors column in flat report worksheet
				
				/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT				
				string strBookSheet;
				int indexLT = index + 1;
				report_get_escaped_data_string(&strBookSheet, indexLT, FALSE, 'D');
				///End FLAT_SHEET_IMPROVEMENT
				for(int iFactor = vstrFactors.GetSize() - 1; iFactor >= 0; iFactor--)
				{
					TreeNode trFactor = trRow.InsertNode(trRow.FirstNode, "Group" + (iFactor+1));
					trFactor.DataID = IDST_STATS_ON_COLS_FLAT_REPORT_GROUP_COL_BEGIN + iFactor;	
					/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
					//trFactor.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_Y);
					trFactor.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_X);
					///End FLAT_SHEET_IMPROVEMENT
					trFactor.strVal = vstrFactors[iFactor];
					
					string strFactorLabel;
					report_get_escaped_data_string(&strFactorLabel, iFactor+1, FALSE, 'A', 0, ESC_LABEL_ADD_NONE, 'F');
					trFactor.SetAttribute(STR_LABEL_ATTRIB, strFactorLabel);						
					trFactor.SetAttribute(STR_USER_PARAM_ATTRIB_PREFIX, _L("Source") + "|" + strBookSheet); /// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
				}
				
				TreeNode trDataLabel = trRow.InsertNode(trRow.FirstNode, "Data");
				///End SHOW_GROUP_COLUMN_IN_FLAT_REPORT_SHEET
				trDataLabel.DataID = IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL;
				trDataLabel.SetAttribute(STR_LABEL_ATTRIB, _L("Data"));
				/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
				//trDataLabel.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_Y);
				trDataLabel.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_X);
				///End FLAT_SHEET_IMPROVEMENT
				/// Iris 07/08/2011 ORG-2427-S2 IMPROVE_DATA_COLUMN_IN_FLAT_REPORT_SHEET
				// For Data column, just put column LN/Short name to cells, and put BookSheet name to XXX Label and the LN/Short name of Weight data to XXX Label
				/*
				string strFullDataLabel = strDataLabel;
				strFullDataLabel.Replace('A', 'I');
				trDataLabel.strVal = strFullDataLabel;		
				*/
				///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
				//trDataLabel.strVal = strDataLabel;				
				trDataLabel.strVals = vsDataLabel;				
				///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
				
				/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
				/*
				string strBookSheet;
				int indexLT = index + 1;
				report_get_escaped_data_string(&strBookSheet, indexLT, FALSE, 'D');
				*/
				trDataLabel.SetAttribute(STR_USER_PARAM_ATTRIB_PREFIX, _L("Source") + "|" + strBookSheet);				
				///End FLAT_SHEET_IMPROVEMENT
				
				// to add weight info to Data column label
				if( IsDatasetHasWeight(trOp.GUI.InputData, index) )
				{
					string strWeightData;
					/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
					//report_get_escaped_data_string(&strWeightData, indexLT, FALSE, 'A', 'W');
					report_get_escaped_data_string(&strWeightData, indexLT, FALSE, 'I', 'W');
					///End FLAT_SHEET_IMPROVEMENT
					string strAttribName = STR_USER_PARAM_ATTRIB_PREFIX + 2;
					trDataLabel.SetAttribute(strAttribName, _L("Weight") + "|" + strWeightData);				
				}
				///End IMPROVE_DATA_COLUMN_IN_FLAT_REPORT_SHEET
				
			}
#endif //__STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT__
			///End STATS_ON_COLS_SUPPORT_FLAT_SHEET_REPORT
			
			/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
			///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
			//addFlatReport(trOp, index, strDataLabel, vstrFactors);
			addFlatReport(trOp, index, vsDataLabel, vstrFactors);
			///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
			///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX

			//adding footnode for the notice of Mod
			if(bMultiModes && index == nTotalNumData - 1)
			{
				addMultiModesFootnote(trOp, nTotalNumData, vstrFactors);
			}	
			
			if(trOp.GUI.Quantities.ExVal.nVal)
			{
				/// Iris 05/14/2007 v8.0617 EXTREME_VALUE_NEED_MORE_GROUP_LABELS
				//addExtremeValuesTable(trOp, index, vData, strDataLabel);
				/// Iris 05/17/2007 v8.0619 GET_ROW_INDEX_FOR_STATS_EXTREME_VAL_TABLE
				//addExtremeValuesTable(trOp, index, vData, strDataLabel, vstrFactors);
				///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
				//addExtremeValuesTable(trOp, index, vData, vintRowsInSource, strDataLabel, vstrFactors);
				addExtremeValuesTable(trOp, index, vData, vintRowsInSource, vsDataLabel, vstrFactors);
				///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
				///end GET_ROW_INDEX_FOR_STATS_EXTREME_VAL_TABLE
				/// end EXTREME_VALUE_NEED_MORE_GROUP_LABELS	
				
				/// Iris 10/22/2012 ORG-7175-P1 FIX_NO_EXTREME_TABLE_CREATED_AFTER_SELECTED_THE_TABEL_IN_CHANGE_PARAM
				TreeNode trTable = trOp.Calculation.ExVals;
				if( trTable && !trTable.Show )
					trTable.Show = true;
				///End FIX_NO_EXTREME_TABLE_CREATED_AFTER_SELECTED_THE_TABEL_IN_CHANGE_PARAM
			}
			/// Iris 11/19/2010 ORG-1535-P1 FOUND_EMPTY_EXTREME_VALUES_REPORT_TABLE_IN_CHANGE_PARAMS
			else if( trOp.Calculation.ExVals.IsValid() )
			{
				trOp.Calculation.ExVals.Show = false;
			}
			///End FOUND_EMPTY_EXTREME_VALUES_REPORT_TABLE_IN_CHANGE_PARAMS
			///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
			//ConvertEscapedString(strDataLabel); 
			ConvertEscapedString(vsDataLabel);
			///------ End DATASET_IDENTIFY_USE_NEW_CONTROL

			/// Iris 11/09/2009 QA81-14599 IMPROVE_STATS_ON_COLS_CALCULATION_SPEED
			if( IsPlotStatsGraph(trOp) )
			///end IMPROVE_STATS_ON_COLS_CALCULATION_SPEED
			{
				///Kyle 11/17/2017 ORG-16895-S1 BOX_SUPPORT_PANEL_REMOVE_OC_CALCULATION_CODES
				//AddBinDataTableAndGraphNodes(trOp, index, vData, vstrFactors, strDataLabel);
				///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
				//AddBinDataTableAndGraphNodes(trOp, index, vData, vWeights, vstrFactors, strDataLabel);
				string strDataLabel;
				CombineDataLabel(strDataLabel, vsDataLabel);
				AddBinDataTableAndGraphNodes(trOp, index, vData, vWeights, vstrFactors, strDataLabel);
				///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
				///End BOX_SUPPORT_PANEL_REMOVE_OC_CALCULATION_CODES
			}
			//return TRUE;
		}

		return TRUE;		
	}							
	///end MOVE_DESCSTATS_TO_BASE_CLASS
	
	///Kyle 08/03/2015 ORG-12921-S1 STATS_ON_COL_SKIP_EMPTY_DATASET
	virtual bool DescStatsExcludeEmptyDataset(TreeNode& trOp)
	{
		TreeNode trExcludeEmpty = trOp.GUI.ExcludeEmpty;
		return trExcludeEmpty && trExcludeEmpty.nVal != 0;
	}
	///End STATS_ON_COL_SKIP_EMPTY_DATASET
	
	enum
	{
		DESC_STATS_WEIGHT_DIRECT_WEIGHTING,
		DESC_STATS_WEIGHT_INSTRUMENTAL,
		DESC_STATS_WEIGHT_STATISTICAL
	};

	//virtual 
	DWORD	GetDataRules(const TreeNode& trOp, bool bIgnoreCombineInfo = false )
	{
		/// Iris 06/06/06 DIFF_INPUT_FORMAT_FOR_COL_AND_ROW
		/////Echo 2/2/05 DRR_BAD_WEIGHT_TREATMENT
		////DWORD dwRet =  DRR_GET_MISSING;
		//DWORD dwRet =  DRR_GET_MISSING | DRR_BAD_WEIGHT_TREATMENT;	
		/////end DRR_BAD_WEIGHT_TREATMENT
		int 	nOption = trOp.GUI.StatsOnRows.nVal;
		DWORD 	dwRet;
		if( 1 != nOption) 
		{
			dwRet =  DRR_GET_MISSING | DRR_BAD_WEIGHT_TREATMENT; //on Columns
			///Kyle 05/29/2014 ORG-10284-S1 TRIM_MISSING_BLANK_VALUES_FROM_GROUPING_COLUMN
			if( OP_GUI_OUTPUT_TABLES_BRANCH(trOp.GUI).MissingData.nVal )
			{
				DRR_SET_FACTORS_MODE(dwRet, DRR_FACTORS_MODE_OFFSET_MISSING);
			}
			else
			{
				DRR_SET_FACTORS_MODE(dwRet, DRR_FACTORS_MODE_TRIM_MISSING);
			}
			///End TRIM_MISSING_BLANK_VALUES_FROM_GROUPING_COLUMN
		}
		else
			dwRet = DRR_GET_MISSING | /*DRR_NO_FACTORS |*/ DRR_NO_WEIGHTS; //on Rows	///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
		///End DIFF_INPUT_FORMAT_FOR_COL_AND_ROW		

		if(GetOptionIndex(trOp.GUI))
			dwRet |= DRR_BY_ROWS;
		/// Iris 5/04/2009 QA80-11982 STATS_ON_COL_ADD_WEIGHT_METHOD
		else
		{
			if( trOp.GUI.Computation.WeightMethod )
			{
				int nWMethod = trOp.GUI.Computation.WeightMethod.nVal;
				switch(nWMethod)
				{
				case DESC_STATS_WEIGHT_DIRECT_WEIGHTING:
					break;
				case DESC_STATS_WEIGHT_INSTRUMENTAL:
					dwRet |= DRR_DEPERR_TO_WEIGHT;
					break;
				case DESC_STATS_WEIGHT_STATISTICAL:
					dwRet |= DRR_DEPERR_TO_WEIGHT | DRR_DEPERR_TO_WEIGHT_STATISTICAL;
					break;
				}
			}
		}
		///end STATS_ON_COL_ADD_WEIGHT_METHOD
		return CheckDataRules(trOp, dwRet, bIgnoreCombineInfo);
	}

	///---Sim 2018-09-28 ORG-19032 FIX_STATS_ON_COLS_TREAT_EMPTY_COLUMN_AS_MISSING
	//virtual
	DWORD	GetDataRules2(const TreeNode& trOperation)
	{
		DWORD 	dwRet = 0;
		if ( DESC_STATS_ON_COLS == trOperation.GUI.StatsOnRows.nVal )
		{
			dwRet |= DRR2_CHECK_IGNORE_EMPTY_COLUMN;
		}

		return dwRet;

	}
	///---END ORG-19032 FIX_STATS_ON_COLS_TREAT_EMPTY_COLUMN_AS_MISSING
	
	/// Iris 9/22/2011 ORG-3208-S1 FIX_REPORT_GRAPH_ISSUE_FOR_MISSED_FACTOR_IN_MULTI_GROUPS_DATA
	// move to statsopbase.h in order to support multiple factors for Normality Test
	/*
	///Sophy 1/5/2009 v8.0993d QA80-12858 GIVE_USEFUL_INFO_ON_REPORT_GRAPH_WITH_FACTOR_VALUE_FOR_STATS_COLUMN
	//virtual
	bool	UpdateReportGraphLabel(TreeNode& trOp, TreeNode& trLabel, int nGraphIndex, int nPicRow, int nPicCol, int nNumPicCols)
	{
		if ( !trOp || !trLabel )
			return false;
		
		int 	nOption = trOp.GUI.StatsOnRows.nVal;
		if ( 1 != nOption ) //stats on column
		{
			DataRange drInput;
			GetInput(drInput);
			if ( drInput )
			{
				/// Iris 9/10/2009 QA80-11710-P2 IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA					
				//int c1, c2, r1, r2;
				//Worksheet wks;
				//int nNumDataset = 0;
				//int nNumRanges = drInput.GetNumRanges();
				//string strName;
				//
				///// Iris 2/19/2009 QA_FOUND_RUNTIME_ERR_IF_CMOBI_SOURCE_DATA_AND_REPORT_INCLUDED_GRAPH
				//if( IsCombinedMultiAsSingle(trOp) )
					//nNumDataset = 1;
				//else
				/////end QA_FOUND_RUNTIME_ERR_IF_CMOBI_SOURCE_DATA_AND_REPORT_INCLUDED_GRAPH
				//{
					//for ( int nSub = 0; nSub < nNumRanges; nSub++)
					//{
						//DataRange drSub;
						//drInput.GetRange(nSub, r1, c1, r2, c2, wks, &strName);
						//if ( strName.CompareNoCase("X") == 0 )  //data range, not grouping range
						//{
							//nNumDataset += c2 - c1 + 1; //in stats on column, when one range cross multi-columns, shoult treat it as muilti-dataset
						//}
					//}
				//}
				//if ( nNumDataset < 1 )
					//return false;
				//int nFactors = GetTotalNumPictureForOneGraphType(trOp, nGraphIndex) / nNumDataset;				
				int nFactors = GetNumFactors(trOp);
				if( nFactors > 0 )
				///end IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA
				{					
					int nFactorIndex = (nNumPicCols * nPicRow + nPicCol) % nFactors;
					vector<string> vsFactors ;
					drInput.GetData(GetDataRules(trOp), nFactorIndex, NULL, NULL, NULL, NULL, NULL, &vsFactors);
					if ( vsFactors.GetSize() > 0 ) //if has factor, should display its value on graph label
					{						
						/// Iris 9/10/2009 QA80-11710-P2 IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA					
						if( IsPlotAllPlotsInOneGraph(trOp) ) // only show data label
						{						
							int nPlotIndex = (nNumPicCols * nPicRow + nPicCol) * nFactors;
							string strDataLabel;
							GetEscapedMainDataString(trOp, strDataLabel, nPlotIndex + 1);
							ConvertEscapedString(strDataLabel);
							trLabel.strVal = strDataLabel;
						}
						else // display data label with factor string
						///end IMPROVE_REPORT_GRAPH_WHEN_PLOT_IN_ONE_GRAPH_WITH_GROUPING_DATA
						{
							ConvertEscapedStrings(trLabel);	
							string strLabel = trLabel.strVal;
							string strFactors;
							strFactors.SetTokens(vsFactors, ',');
							strLabel += " (" + strFactors + ")";
							trLabel.strVal = strLabel;
						}						
					}					
				}
			}
		}
		return true;
	}
	///end GIVE_USEFUL_INFO_ON_REPORT_GRAPH_WITH_FACTOR_VALUE_FOR_STATS_COLUMN
	*/
	///End FIX_REPORT_GRAPH_ISSUE_FOR_MISSED_FACTOR_IN_MULTI_GROUPS_DATA

	// virtual
	string	GetMaskedDataTableErrorColumnName()
	{
		return WKSH_OPERATION_INFO_DATA_WEIGHT;
	}
	
	///Arvin 12/04/06 STATS_ON_ROW_OUTPUT_RESULTS_TO_SHEET
	virtual bool IsOutputDataResultsToNewSheet(const TreeNode& trGUI) 
	{
		return GetOptionIndex(trGUI);
	}
	///end STATS_ON_ROW_OUTPUT_RESULTS_TO_SHEET
	
	///Arvin    03/08/07 SHOULD_NOT_RESCALE_IF_NOT_PLOT_ALL_HISTOGRAMS_IN_ONE_GRAPH_WHEN_HAS_FACTOR by max's suggestion
	int ReportGraphGetRescaleOption(TreeNode& trOp, int nGraphIndex)
	{
		/// Iris 11/05/2009 QA81-14599 FIX_STATS_ON_COLS_PLOT_REPORT_GRAPHS_VERY_SLOW
		// Rescale on Box and Histogram plot, will be separately done in SetupPlotDetails below.
		// SetupPlotDetails will do rescale for each layer for histogram plot when plot all in one graph.
		/*
		if(ReportGetPlotTypeFromGraphIndex(nGraphIndex) == IDM_PLOT_HISTOGRAM_TYPE && !IsPlotAllPlotsInOneGraph(trOp))
			return -1;	
		*/
		return -1;
		///end FIX_STATS_ON_COLS_PLOT_REPORT_GRAPHS_VERY_SLOW
		
		return WksReportOperation::ReportGraphGetRescaleOption(trOp, nGraphIndex);
	}
	///end SHOULD_NOT_RESCALE_IF_NOT_PLOT_ALL_HISTOGRAMS_IN_ONE_GRAPH_WHEN_HAS_FACTOR
	
	///Arvin    03/09/07 SHOULD_SET_AXIS_X_FROM_TO_AND_TITLE_WHEN_USE_DATARANGE_WITH_FACTOR_TO_PLOT_HISTOGRAM by max's suggestion
	bool SetAxisXTitleWithFactor(const TreeNode& trOp, const DataRange dr, GraphLayer& gl, int nDataIndex)
	{
		DWORD dwRules = GetDataRules(trOp);
		vector vData;
		vector<string> vstrFactors;
		bool bGetData = GetDataAndFactorValues(trOp, dr, nDataIndex, vData, vstrFactors);
		if( bGetData && vstrFactors.GetSize() > 0 )
		{
			string strXTitle;
			if(!get_axis_title(gl, strXTitle, 0))
				error_report("Failed to get title of X axis");
			
			string strXSuf, strXPre;
			strXPre = strXTitle;
			strXPre.Delete(0, 5);
			
			if(IsPlotAllPlotsInOneGraph(trOp))
				legend_update(gl, ALM_COMMENT);
			else
				strXSuf = "_" + vstrFactors[0]; 
				
			if(!strXPre.IsEmpty())
			{
				strXTitle.Replace(strXPre, strXSuf);
				strXSuf = "";
			}
			
			strXTitle = strXTitle + strXSuf;
			
			if(!set_axis_title(gl, strXTitle, 0))
				error_report("Failed to set title of X axis");
			
			gl.Rescale();
			return true;
		}
		
		return false;
	}
	
	bool SetAxisXFromTo(const TreeNode& trOp, const DataRange dr, GraphLayer& gl, int nDataIndex)
	{
		DWORD dwRules = GetDataRules(trOp);
		vector vData;
		vector<string> vstrFactors;
		bool bGetData = GetDataAndFactorValues(trOp, dr, nDataIndex, vData, vstrFactors);
		if( bGetData)
		{
			double dMin, dMax, dBinSize;
			vData.GetMinMax(dMin, dMax);
			//int nBins = 0.5 + sqrt(vData.GetSize() + 1);
			gl.Rescale();
			RoundLimits(&dMin, &dMax, &dBinSize);
			double dAbMargin = abs(dMax-dMin)*0.08;
			gl.X.From = dMin - dAbMargin;
			gl.X.To = dMax + dAbMargin;
			return true;
		}
		
		return false;
	}
	
	bool SetupPlotDetails(const TreeNode& trOp, GraphLayer& gl, int nFittedPlot, int nNumPlots = 1, int nGraphIndex = 0, int nDataIndex = 0, bool bIsSourceGraph = false, bool bUpdateExistedReportGraph = false)
	{		
		/// Iris 11/28/2008 HISTOGRAM_SCALE_NOT_GOOD_WHEN_RECALCULATE
		//if( !bUpdateExistedReportGraph ) /// Iris 08/10/2007 QA70-10073 TO_KEEP_CUSTOMIC_SETTINGS_IN_REPORT_GRAPH
		///end HISTOGRAM_SCALE_NOT_GOOD_WHEN_RECALCULATE
		{
			///Arvin 08/22/07 WRONG_HISTOGRAM_SCALE_IN_STATS_ON_COL
			//DataRange dr;
			//GetInput(dr);
			//if(HasFactor(trOp, nDataIndex) && ReportGetPlotTypeFromGraphIndex(nGraphIndex) == IDM_PLOT_HISTOGRAM_TYPE)
			//	SetAxisXTitleWithFactor(trOp, dr, gl, nDataIndex);
			
			//if(ReportGetPlotTypeFromGraphIndex(nGraphIndex) == IDM_PLOT_HISTOGRAM_TYPE && !IsPlotAllPlotsInOneGraph(trOp))
			//	SetAxisXFromTo(trOp, dr, gl, nDataIndex);
			
			/// Iris 11/05/2009 QA81-14599 FIX_STATS_ON_COLS_PLOT_REPORT_GRAPHS_VERY_SLOW
			//gl.Rescale();
			bool bRescale = true;
			///Kyle 08/07/2015 ORG-12921-P1 STATS_ON_COL_SKIP_EMPTY_OUTPUT_PLOTS
			//if( IsPlotAllPlotsInOneGraph(trOp, nGraphIndex) && IDM_PLOT_BOX == ReportGetPlotTypeFromGraphIndex(nGraphIndex) && nFittedPlot != GetNumPlotsInOneGraph(trOp, nGraphIndex) - 1 )
			if( IsPlotAllPlotsInOneGraph(trOp, nGraphIndex) && IDM_PLOT_BOX == ReportGetPlotTypeFromGraphIndex(nGraphIndex) && !DescStatsExcludeEmptyDataset(trOp) && nFittedPlot != GetNumPlotsInOneGraph(trOp, nGraphIndex) - 1 )
			///End STATS_ON_COL_SKIP_EMPTY_OUTPUT_PLOTS
			{
				bRescale = false;
			}
			if( bRescale )
			{
				/// Hong 11/27/09 QA80-14752 FIX_HISTOGRAM_BAD_RESCALE_IF_GRAPH_SHOWN_BEFORE_RECACULATE_WHEN_DATA_CHANGE
				GraphPage		gp;
				gl.GetParent(gp);
				gp.Refresh(TRUE); // Hong, MUST be TRUE
				/// end FIX_HISTOGRAM_BAD_RESCALE_IF_GRAPH_SHOWN_BEFORE_RECACULATE_WHEN_DATA_CHANGE
				gl.Rescale();
			}
			///END WRONG_HISTOGRAM_SCALE_IN_STATS_ON_COL
		}
		
		return WksReportOperation::SetupPlotDetails(trOp, gl, nFittedPlot, nNumPlots, nGraphIndex, nDataIndex, bIsSourceGraph, bUpdateExistedReportGraph);		
	}

private:
	///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
	//virtual
	bool doInsertedColumns(TreeNode& trOperation, int nIndex, int nTotalNumData, Range& rngInput, int nOutputIndex)
	{
		if( !(GetDataRules(trOperation) & DRR_BY_ROWS) )
			return WksReportOperation::doInsertedColumns(trOperation, nIndex, nTotalNumData, rngInput, nOutputIndex);
		
		/// Iris 3/18/2009 FIX_STATS_ON_ROW_INPUT_DATA_GIBBERISH_IN_SCRIPT_WND
		// this logic already exist in doReportSheet, but not in doInsertedColumns
		TreeNode trAutoUpdate = trOperation.Operation.AutoUpdate;
		if(trAutoUpdate)
		{
			if(trAutoUpdate.nVal == AU_NONE)
				ConvertEscapedStrings(trOperation.Calculation);
		}
		///end FIX_STATS_ON_ROW_INPUT_DATA_GIBBERISH_IN_SCRIPT_WND
		
		//bool bOK = UpdateInsertedColumns(trOperation, rngInput, nIndex, nTotalNumData, rngOutput, nOutputIndex);				
		int r1, c1, r2, c2;
		Worksheet wksFirst;
		int nWksCount = find_input_range_bounding_box(rngInput, r1, c1, r2, c2, wksFirst,"X");
		///------ Folger 05/12/2020 ORG-21828-S1 STATS_ON_ROWS_SUPPORT_INPUT_FROM_DIFF_WKS
		//if(nWksCount != 1)
			//return error_report("Desc Stats only support all input data from the same worksheet");		
		///------ End STATS_ON_ROWS_SUPPORT_INPUT_FROM_DIFF_WKS
		TreeNode trOutCol = trOperation.GUI.Output.Report.Column;
		if( trOutCol && PDS_NEW == str_to_predefined_type(trOutCol.strVal) )
			c2 = -1;
		if(c2<0)
			c2 = wksFirst.Columns.Count()-1;
		
		if( !inserted_columns(trOperation, wksFirst, c2, rngInput, nOutputIndex) )
			return error_report("Failed in UpdateInsertedColumns");
		
		return true;
	}
	bool inserted_columns(TreeNode& trOperation, Worksheet& wksOutput, int& nStartCol, const Range& rngInput, int nOutputOption)
	{		
		int 	nCache = updateTableStringMain(trOperation);	
		string 	strName;
		///------ Tony 07/27/2017 ORG-10099-S1 STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END
		//ocu_load_msg_str(IDS_STATS_ON_ROWS_OF, strName, rngInput.GetDescription());
		DataRange drSub;
		if(rngInput.GetSubRange(drSub, DRR_NO_FACTORS | DRR_ONE_DEP_MULTIINDEP))
		{
			string strRange;
			get_smart_range_string(drSub, wksOutput, strRange);
			ocu_load_msg_str(IDS_STATS_ON_ROWS_OF, strName, strRange);
		}
		///------ End STATS_ON_ROWS_RANGE_DESCRIPTION_AND_ADD_NEW_LABEL_END

		vector<int> 		vnLabelTypes, vnJunkLabels;
		bool 				bOK = true;
		int 				nGroup = 0;
		TreeNodeCollection 	tnc(trOperation.Calculation, "Statistics");
		foreach(TreeNode trStatistics in tnc)
		{
			DataRange drOutput;
			bool bHasOutput = GetOutput(drOutput, GetOutputSlot(nGroup, false, nOutputOption));		// at output position 1
			
			if( !InsertReportToWks(trOperation, trStatistics, wksOutput, nStartCol+1, drOutput, SETGRTR_USE_STATIC_LABEL_ROW_POS|SETGRTR_NO_SET_COLUMN_NAME_IN_FLAT_FOR_VECTOR) )
				bOK = false;
			if(drOutput && !drOutput.IsEmpty())
			{
				string strPrefix;
				int	nIndex = string_to_prefix_end_number(strPrefix.GetBuffer(MAXLINE), trStatistics.tagName);				
				if(vnLabelTypes.GetSize() < 1)
					PrepareOuputColLabels(trOperation, rngInput, drOutput, vnLabelTypes, vnJunkLabels);
				if(vnLabelTypes.GetSize() > 0)
					SetOuputColLabels(trOperation, rngInput, nIndex, drOutput, vnLabelTypes, strName, vnJunkLabels);
				
				int c1, c2, numRange = drOutput.GetNumRanges();
				for( int ii = 0; ii < numRange; ii++)
				{
					Worksheet wks;
					string strRange;
					drOutput.GetRange(wks, c1, c2, ii);
					if(c2 == -1)
						c2 = wks.GetNumCols()-1;
					if(c2 > nStartCol)
						nStartCol = c2;
				}
			}
			else
				trStatistics.RemoveAttribute(TREE_UID);
			
			SetOutput(drOutput, GetOutputSlot(nGroup++, false, nOutputOption));	
		}
		
		updateTableStringMain(trOperation, nCache, true);
		
		return bOK;
	}
	///End STATS_ON_ROWS_SUPPORT_GROUPING
	
	/// Hong 07/20/2016 ORG-14278 FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
	#define		STR_CELL_REF_PREFIX						"CELL://"
	bool	check_update_data_identifier_label(string& strDataLabel, int nType, int index)
	{
		if (nType <= RCLT_INVALID || nType >= RCLT_MAX_TYPE)
			return false;

		string		strBookSheetCol;
		int 		indexLT = index + 1;
		report_get_escaped_data_string(&strBookSheetCol, indexLT, FALSE, 'P');
		ConvertEscapedString(strBookSheetCol);

		int		nOffset = -1;
		int		nChar = okutil_cvt_col_label_type_to_char(nType, &nOffset);
		string	strLabelLink;
		if (nOffset >= 0)
			strLabelLink.Format("[%c%d]", (char)nChar, nOffset + 1);
		else
			strLabelLink.Format("[%c]", (char)nChar);
		strDataLabel = STR_CELL_REF_PREFIX + strBookSheetCol + strLabelLink;

		return true;
	}
	/// end FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER

	/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
	/// Hong 07/18/2016 ORG-14278 FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
	BOOL setDataIndentifierInFlatSheet(TreeNode& trDataLabel, int index, LPCSTR strDataLabel, BOOL bAutoUpdateNone, BOOL bCombineMultiAsSingle
									///------ Folger 03/22/2019 ORG-19876-P1 STATS_ON_GRAPH_SLOWNESS
									, TreeNode& trOp
									///------ End STATS_ON_GRAPH_SLOWNESS
									///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
									, int nDataLabelIndex
									///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
									)
	{
		DataRange drInput;
		GetInput(drInput);
		BOOL		bSameSheet = is_multi_ranges_come_from_same_sheet(drInput, "X");

		int 		indexLT = index + 1;
		///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
		//string		strVal = strDataLabel, strCustom;
		/////------ Folger 03/22/2019 ORG-19876-P1 STATS_ON_GRAPH_SLOWNESS
		////int			nType = GetDataIndentifierType(strCustom);
		//int			nType = GetDataIndentifierType(strCustom, &trOp);
		/////------ End STATS_ON_GRAPH_SLOWNESS
		///// Hong 07/22/2016 ORG-14278 FIX_DATA_IDENTIFIER_FAIL_UPDATE_BY_REPORT_SHEET_CONTEXT_MENU
		////if (!check_update_data_identifier_label(strVal, nType, index))
		//if (!bCombineMultiAsSingle && !check_update_data_identifier_label(strVal, nType, index))
		///// end FIX_DATA_IDENTIFIER_FAIL_UPDATE_BY_REPORT_SHEET_CONTEXT_MENU
		//{
			//if (!bSameSheet)
				//report_get_escaped_data_string(&strVal, indexLT, FALSE, 'I');
//
			//if (bAutoUpdateNone)
				//ConvertEscapedString(strVal);
		//}
//
		//vector<string> vsDataLabels;
		//if (!trDataLabel.IsEmpty())
			//vsDataLabels = trDataLabel.strVals;
//
		//vsDataLabels.Add(strVal);
		//trDataLabel.strVals = vsDataLabels;
		
		string strCustom;
		vector<int>	vnType;
		GetDataIndentifierType(vnType, strCustom, &trOp);
		string	strVal = strDataLabel;
		if (!bCombineMultiAsSingle)
		{
			if( nDataLabelIndex >= 0 && nDataLabelIndex < vnType.GetSize())
			{
				if(!check_update_data_identifier_label(strVal, vnType[nDataLabelIndex], index))
				{
					if (!bSameSheet)
						report_get_escaped_data_string(&strVal, indexLT, FALSE, 'I');

					if (bAutoUpdateNone)
						ConvertEscapedString(strVal);
				}
			}
		}
		vector<string> vsNewDataLabels;
		if (!trDataLabel.IsEmpty())
			vsNewDataLabels = trDataLabel.strVals;
		vsNewDataLabels.Add(strVal);

		trDataLabel.strVals = vsNewDataLabels;
		///------ End DATASET_IDENTIFY_USE_NEW_CONTROL

		return bSameSheet;
	}
	/// end FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
	
	///Shadow 12/29/2017 ORG-16287-S1 ADD_UNITS_TO_REPORT_SHEET
	void getInputCommonUnit(string& strInputUnit)
	{
		bool bGetUnit = false;
		string strConsistentUnit;
		DataRange drInput;
		GetInput(drInput);
		int nRangeCount = drInput.GetNumRanges();
		int r1, r2, c1, c2;
		string strName;
		Worksheet wks;
		for (int ii = 0; ii < nRangeCount; ii++)
		{
			drInput.GetRange(ii, r1, c1, r2, c2, wks, &strName);
			if ((wks) && (strcmp(strName, "X") == 0))
			{
				for (int jj = c1; jj <= c2; jj++)
				{
					if (!bGetUnit)
					{
						strConsistentUnit = wks.Columns(jj).GetUnits();
						bGetUnit = true;
					}
					else
					{
						if (strConsistentUnit != wks.Columns(jj).GetUnits())
							return;
					}
				}
			}
		}
		strInputUnit = strConsistentUnit;
	}
	///End ADD_UNITS_TO_REPORT_SHEET
	
	///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
	//void addFlatReport(TreeNode& trOp, int index, LPCSTR strDataLabel, const vector<string>& vstrFactors)
	void addFlatReport(TreeNode& trOp, int index, const vector<string>& vsDataLabel, const vector<string>& vstrFactors)
	///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
	{		
		///------ Folger 07/02/2012 ORG-5592-S1 SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
		/////------ Folger 11/01/2011 ORG-3997-P1 TRANSLATE_OP_STRING_ON_FLAT_SHEET_WHEN_DELETE_DESCSTATS_OPERATION
		//SetConvertEscapeStrForFlatSheet(FALSE);
		/////------ End TRANSLATE_OP_STRING_ON_FLAT_SHEET_WHEN_DELETE_DESCSTATS_OPERATION
		///------ End SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
		/// Iris 10/09/2011 ORG-4047-P1 FIX_NO_FLAT_REPORT_STILL_ADD_RESULT_TO_OPERATION_TREE
		TreeNode trFlatOutBranch = trOp.GUI.Output.FlatOut;			
		if( !trFlatOutBranch )			
			return;		
		
		TreeNode trBook = trFlatOutBranch.Book;
		/// Iris 3/26/2015 ORG-12836-S3 IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
		//TreeNode trResultLog = trFlatOutBranch.AddReportToResultsLog;
		//TreeNode trScript = trFlatOutBranch.DumpScriptWindow;
		//TreeNode trNotes = trFlatOutBranch.DumpNotesWindow;
		//if( !trBook || !trResultLog || !trScript || !trNotes )
		if( !trBook )
		///End IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
			return;
		
		int nBookType = str_to_predefined_type(trBook.strVal);
		/// Iris 3/26/2015 ORG-12836-S3 IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
		//int nNoteWndType = str_to_predefined_type(trNotes.strVal);		
		//if( PDS_NONE == nBookType && 0 == trResultLog.nVal && 0 == trScript.nVal && PDS_NONE == nNoteWndType )
		if( PDS_NONE == nBookType )
		///End IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
			return;
		///End FIX_NO_FLAT_REPORT_STILL_ADD_RESULT_TO_OPERATION_TREE

		///------ Folger 07/02/2012 ORG-5592-S1 SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
		/////------ Folger 11/01/2011 ORG-3997-P1 TRANSLATE_OP_STRING_ON_FLAT_SHEET_WHEN_DELETE_DESCSTATS_OPERATION
		//SetConvertEscapeStrForFlatSheet(TRUE);
		/////------ End TRANSLATE_OP_STRING_ON_FLAT_SHEET_WHEN_DELETE_DESCSTATS_OPERATION
		///------ End SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
		
		TreeNode trStatsTable = trOp.Calculation.Statistics;		
		TreeNode trFlatTable = trOp.ResidualCurves.FlatOut; // ResidualCurves node is the second result curve node, so use this node to do report
		if( !trFlatTable )
		{		
			trFlatTable = trOp.ResidualCurves.AddNode("FlatOut"); 
			/// Iris 9/09/2011 ORG2427-P5 FIX_FLAT_SHEET_NOT_UPDATED_IN_RECALCULATE
			//trFlatTable.Replace( trStatsTable.Clone(), false, true, false );
			///End FIX_FLAT_SHEET_NOT_UPDATED_IN_RECALCULATE
		}			
		///------ Folger 06/12/2014 ORG-11276-P1 STATS_ON_COLUMNS_OUTPUT_FLAT_SHEET_ALLOW_REORDER
		trOp.ResidualCurves.SetAttribute(STR_REPORT_SHEET_ALLOW_REORDER, 1);
		///------ End STATS_ON_COLUMNS_OUTPUT_FLAT_SHEET_ALLOW_REORDER
		/// Iris 9/09/2011 ORG2427-P5 FIX_FLAT_SHEET_NOT_UPDATED_IN_RECALCULATE
		// to only copy all attributes
		///------ Folger 09/03/2020 ORG-22216-P3 OPERATION_TOOLS_SUPPORT_SORT_BY_FACTORS
		//if( 0 == index ) /// Iris 9/21/2011 ORG-2427-P6 FIX_FLAT_REPORT_ONLY_ONE_DATA_RESULT
		if (trStatsTable.Children.Count() == 1)
		///------ End OPERATION_TOOLS_SUPPORT_SORT_BY_FACTORS
		{
			trFlatTable.Replace( trStatsTable.Clone(), false, true, false );
			trFlatTable.Show = true;		///Kyle 08/03/2015 ORG-12921-S1 STATS_ON_COL_SKIP_EMPTY_DATASET
		}
		///End FIX_FLAT_SHEET_NOT_UPDATED_IN_RECALCULATE
		
		string strRowName = CALCULATION_REPORT_TABLE_COL_PREFIX + (index + 1);
		/// Iris 10/11/2011 ORG-4047-P1 CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
		/*
		if( !trFlatRow )
		{
			TreeNode trRow = trStatsTable.GetNode(strRowName);
			if( trRow )
			{
				trFlatRow = trFlatTable.AddNode("tmp");
				trFlatRow.Replace(trRow.Clone(), true, false, false);
				
			}
			else
			{
				error_report("Fail to find Cn node");
				return;
			}
		}			
		// the label and header only used for report table, no need in flat report and notes window...
		trFlatRow.RemoveAttribute(STR_LABEL_ATTRIB);
		int nn = 0;
		string strHeader;
		while( trFlatRow.GetAttribute(STR_SUB_HEADER_ATTRIB_PREFIX+nn, strHeader) )
			trFlatRow.RemoveAttribute(STR_SUB_HEADER_ATTRIB_PREFIX+nn);
		*/		
		TreeNode trStatsRow = trStatsTable.GetNode(strRowName);
		if( !trStatsRow )
		{
			error_report("Invalid stats node");
			return;
		}
		
		const string strTableTagName = "C1";
		TreeNode trFlatRow = trFlatTable.GetNode(strTableTagName);
		if( !trFlatRow )
		{
			trFlatRow = trFlatTable.AddNode(strTableTagName);			
			octree_copy_atts(&trStatsRow, &trFlatRow, STR_ID_ATTRIB);
		}	
		
		/// Iris 11/16/2012 ORG-7449-P1 IMPROVE_STATS_ON_COL_CHANGE_PARAM_SPEED	
		TreeNode trCheck, trQuantities = trOp.GUI.Quantities;
		///End IMPROVE_STATS_ON_COL_CHANGE_PARAM_SPEED
		///Philip 11/26/2012 ORG-7525-P1 FIX_FAIL2CALC_CUSTOMPERCENT_IN_STAT_ON_COL
		TreeNode tr;
		bool bCustPercentChecked = ((tr = trQuantities.Quantiles) && (tr = tr.CustomPercentiles) && tr.nVal);
		///end FIX_FAIL2CALC_CUSTOMPERCENT_IN_STAT_ON_COL
		///Shadow 12/29/2017 ORG-16287-S1 ADD_UNITS_TO_REPORT_SHEET
		string strInputUnit = "";
		getInputCommonUnit(strInputUnit);
		///End ADD_UNITS_TO_REPORT_SHEET
		foreach(TreeNode trStatsCol in trStatsRow.Children)
		{				
			/// Iris 11/16/2012 ORG-7449-P1 IMPROVE_STATS_ON_COL_CHANGE_PARAM_SPEED			
			if( trQuantities )
			{
				trCheck = trQuantities.FindNodeByAttribute(STR_DATAID_ATTRIB, trStatsCol.DataID, true);				
			}						
			
			if( trCheck && TRGP_CHECK == trCheck.ID && trCheck.nVal
				|| (!trCheck && bCustPercentChecked && (trStatsCol.tagName.Find(CALCULATION_PERCENTILE_PREFIX) == 0)) ///Philip 11/26/2012 ORG-7525-P1 FIX_FAIL2CALC_CUSTOMPERCENT_IN_STAT_ON_COL
			  )
			{
			///End IMPROVE_STATS_ON_COL_CHANGE_PARAM_SPEED	
				TreeNode trFlatCol = trFlatRow.GetNode(trStatsCol.tagName);
				if( !trFlatCol )
				{
					trFlatCol = trFlatRow.AddNode(trStatsCol.tagName);

					octree_copy_atts(&trStatsCol, &trFlatCol, STR_DATAID_ATTRIB);
					octree_copy_atts(&trStatsCol, &trFlatCol, STR_ID_ATTRIB);
					octree_copy_atts(&trStatsCol, &trFlatCol, STR_COL_DESIGNATION_ATTRIB);
					octree_copy_atts(&trStatsCol, &trFlatCol, STR_SHOW_ATTRIB);
					octree_copy_atts(&trStatsCol, &trFlatCol, STR_LABEL_ATTRIB);
					///Shadow 12/29/2017 ORG-16287-S1 ADD_UNITS_TO_REPORT_SHEET
					if (strInputUnit != "")
					{
						if ((trStatsCol.DataID == IDE_SAMPLE_SIZE) || (trStatsCol.DataID == IDE_NUM_MISSING) || (trStatsCol.DataID == IDE_SKEWNESS) || 
							(trStatsCol.DataID == IDE_KURTOSIS) || (trStatsCol.DataID == IDE_COV) || (trStatsCol.DataID == IDE_WEIGHTSUM) || 
							(trStatsCol.DataID == IDE_IMIN) || (trStatsCol.DataID == IDE_IMAX) || (trStatsCol.DataID == IDE_RCV))
						{
							//No unit.
						}
						else
						{
							if ((trStatsCol.DataID == IDE_VARIANCE) || (trStatsCol.DataID == IDE_UNCORSUMSQ) || (trStatsCol.DataID == IDE_CORSUMSQ))
							{
								trFlatCol.SetAttribute(STR_UNIT_ATTRIB, strInputUnit + "^2");
							}
							else
							{
								trFlatCol.SetAttribute(STR_UNIT_ATTRIB, strInputUnit);
							}
						}
					}
					///End ADD_UNITS_TO_REPORT_SHEET
				}
				
				vector vData;
				if( !trFlatCol.IsEmpty() )
				{
					vData = trFlatCol.dVals;
					trFlatCol.Reset(true);
				}
				
				double dVal = trStatsCol.dVal;
				vData.Add(dVal);			
				trFlatCol.dVals = vData;
			/// Iris 11/16/2012 ORG-7449-P1 IMPROVE_STATS_ON_COL_CHANGE_PARAM_SPEED	
			}
			///End IMPROVE_STATS_ON_COL_CHANGE_PARAM_SPEED			
		}	
		///End CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE		
				
		///------ Folger 11/29/2012 ORG-7570-P1 SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
		BOOL bAutoUpdateNone = GetAUMode() == AU_NONE;
		///------ End SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION

		/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT				
		string strBookSheet;
		int indexLT = index + 1;
		report_get_escaped_data_string(&strBookSheet, indexLT, FALSE, 'D');
		///------ Folger 11/29/2012 ORG-7570-P1 SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
		if ( bAutoUpdateNone )
			ConvertEscapedString(strBookSheet);
		///------ End SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION

		///End FLAT_SHEET_IMPROVEMENT		
		for(int iFactor = vstrFactors.GetSize() - 1; iFactor >= 0; iFactor--)
		{
			/// Iris 10/11/2011 ORG-4047-P1 CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
			/*
			TreeNode trFactor = trFlatRow.InsertNode(trFlatRow.FirstNode, "Group" + (iFactor+1));	
			trFactor.DataID = IDST_STATS_ON_COLS_FLAT_REPORT_GROUP_COL_BEGIN + iFactor;	
			/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
			//trFactor.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_Y);
			trFactor.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_X);
			///End FLAT_SHEET_IMPROVEMENT
			trFactor.strVal = vstrFactors[iFactor];
			*/
			const string strTagName = "Group" + (iFactor+1);
			TreeNode trFactor = trFlatRow.GetNode(strTagName);
			if( !trFactor )
			{
				///------ Folger 08/23/2013 ORG-8566-P1 STATS_ON_COLUMN_FAILED_IF_NO_OUTPUT
				//trFactor = trFlatRow.InsertNode(trFlatRow.FirstNode, strTagName);
				if ( trFlatRow.FirstNode )
					trFactor = trFlatRow.InsertNode(trFlatRow.FirstNode, strTagName);
				else
					trFactor = trFlatRow.AddNode(strTagName);
				///------ End STATS_ON_COLUMN_FAILED_IF_NO_OUTPUT
				trFactor.DataID = IDST_STATS_ON_COLS_FLAT_REPORT_GROUP_COL_BEGIN + iFactor;	
				trFactor.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_X);
			}
			
			vector<string> vsFactor;
			if( !trFactor.IsEmpty() )
				vsFactor = trFactor.strVals;
			vsFactor.Add( vstrFactors[iFactor] );
			trFactor.strVals = vsFactor;
			///End CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE			
			
			string strFactorLabel;
			report_get_escaped_data_string(&strFactorLabel, iFactor+1, FALSE, 'A', 0, ESC_LABEL_ADD_NONE, 'F');
			///------ Folger 12/05/2012 ORG-7570-P1 SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
			if ( bAutoUpdateNone )
				ConvertEscapedString(strFactorLabel);
			///------ End SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
			trFactor.SetAttribute(STR_LABEL_ATTRIB, strFactorLabel);						
			trFactor.SetAttribute(STR_USER_PARAM_ATTRIB_PREFIX, _L("Source") + "|" + strBookSheet); /// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
			/// Hong 05/21/2014 ORG-11155 OPERATION_RESULT_COPY_CATEGORICAL_INFO
			int			nUID;
			if (IsDatasetHasFactor(trOp.GUI.InputData, nUID))
			{
				DWORD		dwCntrl = SRC_COL_PROPERTY_CATEGORICAL;
				okutil_source_column_property(&trFactor, &nUID, &dwCntrl, FALSE);
			}
			/// end OPERATION_RESULT_COPY_CATEGORICAL_INFO
		}		
		
		///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
		//const string strDataNodeTagName = "Data";
		//TreeNode trDataLabel = trFlatRow.GetNode(strDataNodeTagName);
//
		/////------ Folger 05/31/2012 ORG-5592-S1 SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
		//if ( !IsOutputDataIdentifierFlatSheet(&trOp) )
		//{
			//if ( trDataLabel )
				//trDataLabel.Remove();
			//return;
		//}
		/////------ End SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
//
		//if( !trDataLabel )
		/////------ Folger 05/03/2013 ORG-8566-P1 STATS_ON_COLUMN_FAILED_IF_NO_OUTPUT
			////trDataLabel = trFlatRow.InsertNode(trFlatRow.FirstNode, strDataNodeTagName);
		//{
			//if ( trFlatRow.FirstNode )
				//trDataLabel = trFlatRow.InsertNode(trFlatRow.FirstNode, strDataNodeTagName);
			//else
				//trDataLabel = trFlatRow.AddNode(strDataNodeTagName);
		//}
		/////------ End STATS_ON_COLUMN_FAILED_IF_NO_OUTPUT
		/////End SHOW_GROUP_COLUMN_IN_FLAT_REPORT_SHEET
		//trDataLabel.DataID = IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL;
		//trDataLabel.SetAttribute(STR_LABEL_ATTRIB, GetLocalized(strDataNodeTagName));
		///// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
		////trDataLabel.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_Y);
		//trDataLabel.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_X);
		/////End FLAT_SHEET_IMPROVEMENT
		///// Iris 07/08/2011 ORG-2427-S2 IMPROVE_DATA_COLUMN_IN_FLAT_REPORT_SHEET
		//// For Data column, just put column LN/Short name to cells, and put BookSheet name to XXX Label and the LN/Short name of Weight data to XXX Label
		///*
		//string strFullDataLabel = strDataLabel;
		//strFullDataLabel.Replace('A', 'I');
		//trDataLabel.strVal = strFullDataLabel;		
		//*/
		///// Hong 07/18/2016 ORG-14278 FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
		////DataRange drInput;
		////GetInput(drInput);
		////if( is_multi_ranges_come_from_same_sheet(drInput, "X") )
		////{
		////	/// Iris 10/11/2011 ORG-4047-P1 CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
		////	//trDataLabel.strVal = strDataLabel;
		////	vector<string> vsDataLabels;
		////	if( !trDataLabel.IsEmpty() )
		////		vsDataLabels = trDataLabel.strVals;
		////	///------ Folger 11/29/2012 ORG-7570-P1 SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
		////	//vsDataLabels.Add( strDataLabel );
		////	if ( bAutoUpdateNone )
		////	{
		////		string str = strDataLabel;
		////		ConvertEscapedString(str);
		////		vsDataLabels.Add(str);
		////	}
		////	else
		////	{
		////		vsDataLabels.Add(strDataLabel);
		////	}
		////	///------ End SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
		////	trDataLabel.strVals = vsDataLabels;
		////	///End CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
		////	
		////	/// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
		////	/*
		////	string strBookSheet;
		////	int indexLT = index + 1;
		////	report_get_escaped_data_string(&strBookSheet, indexLT, FALSE, 'D');
		////	*/
		////	trDataLabel.SetAttribute(STR_USER_PARAM_ATTRIB_PREFIX, _L("Source") + "|" + strBookSheet);				
		////}
		////else
		////{
		////	trDataLabel.RemoveAttribute(STR_USER_PARAM_ATTRIB_PREFIX);
		////	string strBookSheetCol;
		////	report_get_escaped_data_string(&strBookSheetCol, indexLT, FALSE, 'I');
		////	///------ Folger 12/05/2012 ORG-7570-P1 SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
		////	if ( bAutoUpdateNone )
		////		ConvertEscapedString(strBookSheetCol);
		////	///------ End SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
		////	/// Iris 10/11/2011 ORG-4047-P1 CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
		////	//trDataLabel.strVal = strBookSheetCol;
		////	vector<string> vsDataLabels;
		////	if( !trDataLabel.IsEmpty() )
		////		vsDataLabels = trDataLabel.strVals;
		////	vsDataLabels.Add( strBookSheetCol );
		////	trDataLabel.strVals = vsDataLabels;
		////	///End CHANGE_FLAT_SHEET_OPERATION_TREE_FORMAT_TO_REDUCE_OPJ_SIZE
		////}
		//BOOL	bCombineMultiAsSingle = IsCombinedMultiAsSingle(trOp);
		//BOOL	bDataFromSameSheet = setDataIndentifierInFlatSheet(trDataLabel, index, strDataLabel, bAutoUpdateNone, bCombineMultiAsSingle
																/////------ Folger 03/22/2019 ORG-19876-P1 STATS_ON_GRAPH_SLOWNESS
																//, trOp);
																/////------ End STATS_ON_GRAPH_SLOWNESS
//
		//if (bDataFromSameSheet)
			//trDataLabel.SetAttribute(STR_USER_PARAM_ATTRIB_PREFIX, _L("Source") + "|" + strBookSheet);				
		//else
			//trDataLabel.RemoveAttribute(STR_USER_PARAM_ATTRIB_PREFIX);
		///// end FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
		/////End FLAT_SHEET_IMPROVEMENT
		//
		//// to add weight info to Data column label
		//if( IsDatasetHasWeight(trOp.GUI.InputData, index) )
		//{
			//string strWeightData;
			///// Iris 7/22/2011 ORG-2427-S3 FLAT_SHEET_IMPROVEMENT
			////report_get_escaped_data_string(&strWeightData, indexLT, FALSE, 'A', 'W');
			//report_get_escaped_data_string(&strWeightData, indexLT, FALSE, 'I', 'W');
			/////End FLAT_SHEET_IMPROVEMENT
			/////------ Folger 12/05/2012 ORG-7570-P1 SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
			//if ( bAutoUpdateNone )
				//ConvertEscapedString(strWeightData);
			/////------ End SHOULD_CONVERT_ESCAPED_STR_IF_NO_OPERATION
			//string strAttribName = STR_USER_PARAM_ATTRIB_PREFIX + 2;
			//trDataLabel.SetAttribute(strAttribName, _L("Weight") + "|" + strWeightData);				
		//}
		UpdateDataIdentifiersFlatSheet(trOp, vsDataLabel, index);
		///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
	}
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
	
	/// Iris 5/26/2008 WRONG_RESULT_CURVE_SHEET_NAME_SAME_AS_REPORT_SHEET
	/*
	///Arvin 06/19/07 WRONG_HISTOGRAM_AND_BOXCHART_PLOTS_WHILE_DATA_HAVE_FACTORS
	void getGUIResultCurveNode(const TreeNode& trGUI, TreeNode& trResultCurve, int nOutputIndex = OUTPUT_RESULT_CURVE_FIT_CURVES_SHEET)
	{
		if(nOutputIndex == OUTPUT_RESULT_CURVE_FIT_CURVES_SHEET)
			trResultCurve = trGUI.Output.Report;
	}
	///end WRONG_HISTOGRAM_AND_BOXCHART_PLOTS_WHILE_DATA_HAVE_FACTORS
	*/
	//virtual
	string GetCurveOutputBookName(const TreeNode& trGUI, int nOutputIndex, int* pnSpecialType = NULL, Worksheet* pwksReport = NULL)
	{
		/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH	
		if( OUTPUT_FLAT_RESULT_SHEET == nOutputIndex /*&& trFlatOut*/ )
		{		
 			return StatsOpBase::GetCurveOutputBookName(trGUI, nOutputIndex, pnSpecialType, pwksReport);
		}
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX

		string	strBook;
		if(NULL != pwksReport)
		{
			///Sophy 9/3/2008 FIX_RUNTIME_ON_NO_REPORT_BOOK_WHEN_DO_STATS_ON_COLUMN
			//strBook = pwksReport->GetPage().GetName();
			if( pwksReport->IsValid() )
				strBook = pwksReport->GetPage().GetName();
			///end FIX_RUNTIME_ON_NO_REPORT_BOOK_WHEN_DO_STATS_ON_COLUMN
		}
		return strBook;
	}
	
	//virtual 
	void 	GetResultCurveBookSheetName(TreeNode& trOperation, string& strBookName, string& strSheetName, int nIndex = 0, int nOption = OUTPUT_RESULT_CURVE_FIT_CURVES_SHEET, bool bSeparateSheetForDataset = false, int nSheetNameIndex = 0)
	{
		/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifndef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
		strSheetName = _LE(E_STR_DEST_STATS_CURVE_SHEET_NAME);
#else 
		if( OUTPUT_FLAT_RESULT_SHEET == nOption )
			StatsOpBase::GetResultCurveBookSheetName(trOperation, strBookName, strSheetName, nIndex, nOption, bSeparateSheetForDataset, nSheetNameIndex);
		else
			strSheetName = E_STR_DEST_STATS_CURVE_SHEET_NAME;
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
		///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
	}
	///end WRONG_RESULT_CURVE_SHEET_NAME_SAME_AS_REPORT_SHEET
	
	void	addMultiModesFootnote(const TreeNode& trOp, int nTotalNumData, const vector<string> &vstrFactors)
	{
		//----- CPY 10/24/07 LOCALIZATION_CLEAN_UP_ON_OPERATION_CODES
		//string 	strFooter = "Multiple modes exist. The smallest value is shown."; //for only one data case
		string 	strFooter = "Err: not in oErrMsg->Multiple modes exist. The smallest value is shown.";
		ocu_load_msg_str(IDS_MULTI_MODES_EXIST_NO_ARG, strFooter);
		//-----
		if( nTotalNumData > 1 )
		{			
			if(vstrFactors && vstrFactors.GetSize() > 0)//for the case that includes multiple data with grouping data format
			{
				DataRange 	dr;
				dr.Create(trOp.GUI.InputData, false);
				if(dr)
				{				
					int 		r1,c1,r2,c2;
					Worksheet 	wks;
					dr.GetRange("X", r1, c1, r2, c2, wks); //"X", the range name of Input Data, the range name of grouping data is "F"
					Column 		col = wks.Columns(r1);
					if(col)
					{
						//----- CPY 10/24/07 LOCALIZATION_CLEAN_UP_ON_OPERATION_CODES
						//strFooter = "Multiple modes exist in " + col.GetName() + ".The smallest value is shown";
						ocu_load_msg_str(IDS_MULTI_MODES_EXIST, strFooter, col.GetName());
						//-----
					}
				}
			}
			else  // for the case that includes multiple data without grouping data format
			{
				string 	strDataLabelList;
				for(int ii=0; ii<nTotalNumData; ii++)
				{
					int		nRowColIndex;
					string 	strDataLabel;
					///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
					//GetOneDataLabel(trOp, ii, nRowColIndex, strDataLabel);
					//ConvertEscapedString(strDataLabel);
					vector<string> vsDataLabel;
					GetOneDataLabel(trOp, ii, nRowColIndex, vsDataLabel);
					
					CombineDataLabel(strDataLabel, vsDataLabel);
					ConvertEscapedString(strDataLabel);
					///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
					strDataLabelList += strDataLabel + ",";
				}
				strDataLabelList.TrimRight(',');
				//----- CPY 10/24/07 LOCALIZATION_CLEAN_UP_ON_OPERATION_CODES
				//strFooter = "Multiple modes exist in " + strDataLabelList + ". The smallest value is shown.";
				ocu_load_msg_str(IDS_MULTI_MODES_EXIST, strFooter, strDataLabelList);
				//-----
				
			}
		}
		TreeNode trTable = tree_get_node_by_id(trOp.Calculation, IDST_DESC_STATS_RESULTS, true);
		TreeNode trFooter = tree_check_get_node(trTable, "Footnote", IDE_FOOTNOTE_BEGIN, TREE_Footnote, "1"); // just need the TREE_Footnote attribute, value does not matter, so 1 is good
		trFooter.strVal = strFooter;				
	}
	
	void	updateExtremeValuesTableLabel(TreeNode& trRow)
	{
		trRow.Index.SetAttribute(STR_LABEL_ATTRIB, "Index");
		trRow.Value.SetAttribute(STR_LABEL_ATTRIB, "Value");
	}
	///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
	//bool 	addExtremeValuesTable(TreeNode& trOp, int index, const vector& vData, const vector<int>& vintRowsInSource, LPCSTR lpcszDataLabel, vector<string>& vstrFactors)
	bool 	addExtremeValuesTable(TreeNode& trOp, int index, const vector& vData, const vector<int>& vintRowsInSource, const vector<string>& vsDataLabel, vector<string>& vstrFactors)
	///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
	{		
		vector 			vDataTemp;
		vDataTemp = vData;
		vector<int>		vnIndex;
		vnIndex = vintRowsInSource;
		
		// sort and remove missing values
		vector<uint> vnIndeces;
		vDataTemp.Sort(SORT_ASCENDING, true, vnIndeces);
		vnIndex.Reorder(vnIndeces);
		/// Iris 05/18/2007 v8.0621 CORRECT_BAD_LOOP
		//while(vDataTemp.GetSize() > 0 && is_missing_value(vDataTemp[0]) )
		//{			
			//vDataTemp.RemoveAt(0);
			//vnIndex.RemoveAt(0);
		//}
		int 	nNumOfTrim = vDataTemp.TrimLeft(true);
		
		/// Zech 09/12/2012 ORG-5703-P3 FIX_EXTREME_VALUE_INDEX_IN_STATISTICS_IN_COLUMN
		//vDataTemp.GetSubVector(vDataTemp, nNumOfTrim, vDataTemp.GetSize());
		//vnIndeces.GetSubVector(vnIndeces, nNumOfTrim, vnIndeces.GetSize());
		vnIndex.GetSubVector(vnIndex, nNumOfTrim, vnIndex.GetSize());
		/// END FIX_EXTREME_VALUE_INDEX_IN_STATISTICS_IN_COLUMN
		///end CORRECT_BAD_LOOP
		
		// check and get the row of extreme value in table
		int nDataSize = vDataTemp.GetSize();
		int nRow = 5;
		if( nDataSize < 10 )
		{
			nRow = nDataSize / 2;
		}
		if( nRow < 2 )
			return false;		
		
		ExVals *pstExHighVals, *pstExLowVals;
		pstExHighVals = (ExVals*)calloc(nRow, sizeof(ExVals));
		pstExLowVals = (ExVals*)calloc(nRow, sizeof(ExVals));
		
		if( getExtremeVals(vDataTemp, vnIndex, pstExHighVals, pstExLowVals, nRow))
		{		
			TreeNode 	trTable = tree_check_get_node(trOp.Calculation, "ExVals", IDST_DESC_STATS_EXTREME_VALS, STR_LABEL_ATTRIB, _L("Extreme Values") );
			/// Iris 01/15/2007 v8.0541 REMOVE_SUB_TABLE_FROM_ANOVE_MISS_MASK_DATA_TABLE
			/*
			TreeNode	trOneSet = check_add_enumerated_node(trTable, CALCULATION_REPORT_TABLE_COL_PREFIX, index + 1, IDST_TEMP_ONE_SET, STR_LABEL_ATTRIB, lpcszDataLabel);
			trOneSet.ID = IDST_DESC_STATS_EXTREME_VALS + index + 1;
			
			int nRows=0;
			for(int ii=0; ii<nRow; ii++)
			{
				TreeNode trRow = tree_check_get_node(trOneSet, "row" + nRows, IDST_TEMP_ONE_SET, STR_LABEL_ATTRIB, "Highest");
				trRow += pstExHighVals[ii];
				trRow.ID = make_one_set_ID(IDST_DESC_STATS_EXTREME_VALS, index + nRows);
				updateExtremeValuesTableLabel(trRow);
				nRows++;
			}
			
			for(ii=0; ii<nRow; ii++)
			{
				TreeNode trRow = tree_check_get_node(trOneSet, "row" + nRows, IDST_TEMP_ONE_SET, STR_LABEL_ATTRIB, "Lowest");
				trRow += pstExLowVals[ii];
				trRow.ID = make_one_set_ID(IDST_DESC_STATS_EXTREME_VALS, index + nRows);
				updateExtremeValuesTableLabel(trRow);
				nRows++;
			}
			*/			
			///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
			//addRowToExtremeValueTable(trTable, pstExHighVals, nRow, lpcszDataLabel, vstrFactors, "Highest");
			//addRowToExtremeValueTable(trTable, pstExLowVals, nRow, lpcszDataLabel, vstrFactors, "Lowest");
			addRowToExtremeValueTable(trTable, pstExHighVals, nRow, vsDataLabel, vstrFactors, "Highest");
			addRowToExtremeValueTable(trTable, pstExLowVals, nRow,vsDataLabel, vstrFactors, "Lowest");
			///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
			///end REMOVE_SUB_TABLE_FROM_ANOVE_MISS_MASK_DATA_TABLE
		}
		free(pstExHighVals);
		free(pstExLowVals);
		
		return true;
	}

	///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
	//bool 	addRowToExtremeValueTable(TreeNode& trTable, ExVals* pExVals, int nRows, LPCSTR lpcszDataLabel, const vector<string>& vstrFactors, LPCSTR lpcszRowLabel) 
	bool 	addRowToExtremeValueTable(TreeNode& trTable, ExVals* pExVals, int nRows, const vector<string>& vsDataLabel, const vector<string>& vstrFactors, LPCSTR lpcszRowLabel) 
	///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
	{
		int 	nRow = trTable.GetNodeCount();
		for(int ii=0; ii<nRows; ii++)
		{
			///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
			//TreeNode 	trRow = tree_check_get_node(trTable, CALCULATION_REPORT_TABLE_ROW_PREFIX + (nRow+1), IDST_TEMP_ONE_SET, STR_LABEL_ATTRIB, lpcszDataLabel);
			///// Iris 05/14/2007 v8.0617 EXTREME_VALUE_NEED_MORE_GROUP_LABELS
			////tree_add_one_label(trRow, lpcszRowLabel, 0);
			//tree_add_more_labels(trRow, vstrFactors);
			//tree_add_one_label(trRow, lpcszRowLabel, vstrFactors.GetSize());
			/////end EXTREME_VALUE_NEED_MORE_GROUP_LABELS
			vector<string> vsLabel;
			vsLabel = vsDataLabel;
			vsLabel.Append(vstrFactors);
			vsLabel.Add(lpcszRowLabel);
			TreeNode 	trRow = tree_check_get_node(trTable, CALCULATION_REPORT_TABLE_ROW_PREFIX + (nRow+1), IDST_TEMP_ONE_SET);
			tree_add_labels(trRow, &vsLabel);
			///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
			trRow.ID = make_one_set_ID(IDST_DESC_STATS_EXTREME_VALS, nRow);
			
			for(int col=0; col<2; col++)
			{
				string 		strColLabel = 0 == col? "Index" : "Value";
				TreeNode 	trCol = tree_check_get_node(trRow, strColLabel, col + 1, STR_LABEL_ATTRIB, strColLabel);
				if(0 == col)
					trCol.dVal = pExVals[ii].Index;
				else
					trCol.dVal = pExVals[ii].Value;
			}
			
			nRow++;
		}
		return true;
		
	}
	
	bool 	getExtremeVals(const vector& vData, const vector<int>& vIndex, ExVals *pstExHighVals, ExVals *pstExLowVals, int nSize)
	{		
		int 	ii, index=0;
		for(ii=0; ii<nSize; ii++)
		{
			pstExLowVals[index].Index = vIndex[ii];
			pstExLowVals[index].Value = vData[ii];
			index++
		}
		
		index=0;
		for(ii=vData.GetSize()-1; ii>=vData.GetSize()-nSize; ii--)
		{
			pstExHighVals[index].Index = vIndex[ii];
			pstExHighVals[index].Value = vData[ii];
			index++;
		}		
		
		
		return true;
	}
	
	/// Hong 08/13/09 QA80-14138 REDUCE_OPERATION_SIZE_OF_STATS_ON_COLS
#ifdef		__REDUCE_STATS_ON_COLS_OP_MEM_CONSUME__
	//virtual 
	/// Hong 12/11/09 QA80-14138-P2 FIX_STATS_ON_COL_CHANGE_PARAM_CANNOT_ADD_BACK_MISSING_TABLE
	///// Iris 9/03/2009 QA80-14138 FIX_STATS_ON_COL_CHANGE_PARAM_CANNOT_ADD_MISSING_TABLE
	bool	isFilterNeedCloneTree() { return false; }
	//bool isResetHiddenTable() { return true; }
	/////end FIX_STATS_ON_COL_CHANGE_PARAM_CANNOT_ADD_MISSING_TABLE
	/// end FIX_STATS_ON_COL_CHANGE_PARAM_CANNOT_ADD_BACK_MISSING_TABLE
#endif		//__REDUCE_STATS_ON_COLS_OP_MEM_CONSUME__
	/// end REDUCE_OPERATION_SIZE_OF_STATS_ON_COLS

/// Thomas 6/1/06 REDEFINE_UPDATEDATASOURCEINREPORTINGHEADER_FOR_DESCSTATS

protected:
		///------ Folger 03/24/2015 ORG-12824-S1 ALLOW_REMOVE_SHEET_OUTPUT_FROM_OPERATION
	virtual void RemovePartialOutputFromGUI(TreeNode& trGUI, TreeNode& trResult)
	{
		if (DESC_STATS_ON_COLS == trGUI.StatsOnRows.nVal)
		{
			switch (trResult.ID)
			{
			case IDST_RESULT_CURVES:
				trGUI.Plots.Graph1.Use = 0;
				trGUI.Plots.Graph2.nVal = 0;
				return;
			case IDST_RESIDUAL_CURVES:
				trGUI.Output.FlatOut.Book.strVal = STR_NONE;
				return;
			default:
				break;
			}
		}
		StatsOpBase::RemovePartialOutputFromGUI(trGUI, trResult);
	}
	///------ End ALLOW_REMOVE_SHEET_OUTPUT_FROM_OPERATION
	/// Hong 05/21/2014 ORG-11155 OPERATION_RESULT_COPY_CATEGORICAL_INFO
	bool	IsDatasetHasFactor(TreeNode& trInput, int& nColUID, int nIndex = 0)
	{
		if (nIndex >= trInput.Children.Count())
			return false;

		TreeNode	trSubRange = trInput.Children.Item(nIndex);
		if (!trSubRange.F || trSubRange.F.IsEmpty())
			return false;

		DataRange	rng;
		rng.Add("X", trSubRange.F.strVal);
		Worksheet	wks;
		int			nC1, nC2;
		if (!rng.GetRange(wks, nC1, nC2))
			return false;
		
		Column		cc(wks, nC1);
		nColUID = cc.GetUID(TRUE);
		return true;
	}
	/// end OPERATION_RESULT_COPY_CATEGORICAL_INFO
	
	///Arvin 08/17/07 ADD_WEIGHT_DATA_TABLE_IN_INPUT_DATA_TABLE
	///------ Tony 03/01/2018 ORG-117833-P1 IS_DATASET_HAS_WEIGHT_STRICT_JUDGE
	//virtual bool IsDatasetHasWeight(TreeNode& trInput, int nIndex = 0, string& strWeight = NULL)
	virtual bool IsDatasetHasWeight(TreeNode& trInput, int nIndex = 0, string& strWeight = NULL, BOOL bIsStrictWeight = FALSE)
	///------ End IS_DATASET_HAS_WEIGHT_STRICT_JUDGE
	{
		///------ Folger 10/12/2010 ORG-1240-P1 FAILED_TO_SHOW_WEIGHT_DATA_IN_REPORT_INPUT_OTHER_THAN_FIRST_DATA
		/*
		int ii = 0;
		foreach(TreeNode trRange in trInput.Children)
		{
			if(ii == nIndex)
			{
				if(trRange.W && !trRange.W.IsEmpty() )
				{
					if(strWeight)
						strWeight = trRange.W.strVal;
					
					return true;
				}
				else
					return false;
			}
			
			ii++;
		}			
		*/
		TreeNode	trWeight = trInput.Range1.W;
		if ( trWeight && !trWeight.IsEmpty() )
		{
			if ( strWeight )
				strWeight = trWeight.strVal;
			return true;
		}
		///------ End FAILED_TO_SHOW_WEIGHT_DATA_IN_REPORT_INPUT_OTHER_THAN_FIRST_DATA
		return false;
	}	
	///end ADD_WEIGHT_DATA_TABLE_IN_INPUT_DATA_TABLE
	
	///Arvin 08/14/07 WRONG_HISTOGRAM_AND_BOXCHART_PLOT_WHEN_COMBINED_MUTI_AS_SINGLE_DATASET
	bool	IsCombinedMultiAsSingle(const TreeNode& trOp)
	{	
		DataRange dr;
		GetInput(dr);
		DWORD	dwRules = GetDataRules(trOp);
		dwRules &= ~DRR_COMBINED_SIMPLE;
		
		int 	nNumData = dr.GetNumData(dwRules);
		int	modeMDInput = tree_get_oper_multidata_modes(trOp.GUI);
		if(modeMDInput == MDINPUT_CMBND_SIMPLE && nNumData > 1)
			return true;
		
		return false;
	}
	///end WRONG_HISTOGRAM_AND_BOXCHART_PLOT_WHEN_COMBINED_MUTI_AS_SINGLE_DATASET
	
	///Arvin 06/19/07 WRONG_HISTOGRAM_AND_BOXCHART_PLOTS_WHILE_DATA_HAVE_FACTORS
	bool IsOutputSeparateResultCurveSheet(const TreeNode& trOp) 
	{
		///Arvin 08/14/07 WRONG_HISTOGRAM_AND_BOXCHART_PLOT_WHEN_COMBINED_MUTI_AS_SINGLE_DATASET
		//if(HasFactor(trOp))
		///Kyle 11/17/2017 ORG-16895-S1 BOX_SUPPORT_PANEL_REMOVE_OC_CALCULATION_CODES
		//if(HasFactor(trOp) || IsCombinedMultiAsSingle(trOp))
		if(IsNeedSeparateBinDataResultCurveSheet(trOp))
		///End BOX_SUPPORT_PANEL_REMOVE_OC_CALCULATION_CODES
		///end 	WRONG_HISTOGRAM_AND_BOXCHART_PLOT_WHEN_COMBINED_MUTI_AS_SINGLE_DATASET
		{
			int nOption = GetOptionIndex(trOp.GUI);
			if(nOption <= 0)
			{
				foreach(TreeNode trPlot in trOp.GUI.Plots.Children)
				{
					//if(trPlot.nVal)
					if(tree_is_true(trPlot))
						return true;
				}
			}
		}
		
		return false;
	}
	
/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH	
	//virtual 
	bool		IsOutputSeparateResidualCurveSheet(const TreeNode& trOp) 
	{ 
		TreeNode trFlatOut = trOp.GUI.Output.FlatOut;
		if( !trFlatOut || trFlatOut && 0 == trFlatOut.Use )
			return false;
		
		int nBookType = str_to_predefined_type(trFlatOut.Book.strVal);
		if( PDS_NONE != nBookType )
			return true;
		return false;
	}
	
	//virtual 
	TreeNode	GetResidualOutputBranch(const TreeNode& trGUI)
	{
		return trGUI.Output.FlatOut;		
	}	

	//virtual
	string GetResultCurveBookName(TreeNode& trOperation, int nDataIndex = 0, int nOption = -1, bool bSeparateSheetForDataset = false) 
	{
		if( OUTPUT_FLAT_RESULT_SHEET == nOption )
			return _L("Flat Report");
		return "";
	}
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH

	/// Iris 3/26/2015 ORG-12836-S3 IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
	/*
	//virtual 
	TreeNode GetScriptWindowGUINode(const TreeNode& trGUI) 
	{ 
		if(GetOptionIndex(trGUI))
			return StatsOpBase::GetScriptWindowGUINode(trGUI);		
		return trGUI.Output.FlatOut.DumpScriptWindow; 
	}
	
	//virtual 
	TreeNode GetNotesWindowGUINode(const TreeNode& trGUI) 
	{ 
		if(GetOptionIndex(trGUI))
			return StatsOpBase::GetNotesWindowGUINode(trGUI);
		return trGUI.Output.FlatOut.DumpNotesWindow; 
	}
	
	//virtual 
	TreeNode GetResultLogGUINode(const TreeNode& trGUI) 
	{ 
		if(GetOptionIndex(trGUI))
			return StatsOpBase::GetResultLogGUINode(trGUI);
		return trGUI.Output.FlatOut.AddReportToResultsLog; 
	}	
	*/
	///End IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
	
	TreeNode GetResultCuveOutputBranch(const TreeNode& trOp)
	{
		TreeNode 	trCurveBranch = trOp.GUI.Output.Report;
		return 		trCurveBranch;
	}
	///end 	WRONG_HISTOGRAM_AND_BOXCHART_PLOTS_WHILE_DATA_HAVE_FACTORS
	// virtual
	///Arvin 07/25/07 v8.0667 WRONG_INPUT_DATA_TABLE_FOR_MULTI_DATA_AND_FACTORS
	/*
	void UpdateDataSourceInReportingHeader(TreeNode &trInputTable, const vector<string> &vstrFactors, int ii, LPCSTR lpcszXLabel = NULL, int numSubRanges = 0, DWORD dwRules = 0)
	{
		if(!vstrFactors.GetSize())
			WksReportOperation::UpdateDataSourceInReportingHeader(trInputTable, vstrFactors, ii, lpcszXLabel, numSubRanges, dwRules);
		else {
			if (0 != ii)
				return;	
			int	indexRow = 0;
			int	numFcts = vstrFactors.GetSize();
			AddOneRowToInputDataTable(trInputTable, indexRow++, 'D');
			AddOneRowToInputDataTable(trInputTable, indexRow++, 'F', numFcts < 2 ? -1 : 0);	
		}
	}
	*/
	void UpdateDataSourceInReportingHeader(TreeNode& trOp, vector<string>&vstrFactors, Worksheet& wksInputData, int nIndex, int numSubRanges = 0, DWORD dwRules = 0) ///Arvin 07/19/07 v8.0662 WRONG_INPUT_DATA_TABLE_FOR_ROCCURVE
	{
		if(nIndex != 0)
			return;
		
		///Sophy 7/10/2008 FIX_WRONG_INPUT_INFORMATION_WHEN_COMBINE_AS_SINGLE_DATASET_WHILE_STATS_ON_COLUMN
		//reset dwRules to care the combine bit. 
		dwRules = GetDataRules( trOp );
		///end FIX_WRONG_INPUT_INFORMATION_WHEN_COMBINE_AS_SINGLE_DATASET_WHILE_STATS_ON_COLUMN
		string strDataLabel= _L("Data"), strFactorLabel = _L("Group");
		AddMultiInputDataWithFactorSourceTable(trOp, strDataLabel, strFactorLabel, dwRules); 
		
	}
	///END WRONG_INPUT_DATA_TABLE_FOR_MULTI_DATA_AND_FACTORS
/// End REDEFINE_UPDATEDATASOURCEINREPORTINGHEADER_FOR_DESCSTATS
	/// Harvey 05/14/2018 ORG-15972-S1 CHECK_MAKE_GROUP_INPUT_AS_CATEGORICAL
	//virtual
	BOOL	GUItoOperation(TreeNode& trOp, int nFrom)// = GUI_OP_NEW);
	{
		BOOL bRet = StatsOpBase::GUItoOperation(trOp, nFrom);
		int nOption = trOp.GUI.StatsOnRows ? trOp.GUI.StatsOnRows.nVal : -1;
		if(DESC_STATS_ON_COLS == nOption)
		{
			check_set_range_node_as_categorical(trOp.GUI.InputData);
		}
		
		return bRet;
	}
	/// END CHECK_MAKE_GROUP_INPUT_AS_CATEGORICAL

	///Cheney 2007-5-23 QA70-9805 SPEED_UP_STATISTIC_ON_ROW
	//virtual
	bool	CalcMultiData(TreeNode& trOp, DataRange& dr, int &nTotalNumData, int nExeMode, DWORD dwExecCntrl = 0)
	{
		int 	nOption = trOp.GUI.StatsOnRows.nVal;
		/// Iris 11/22/2011 ORG-4373-P1 KEEP_MISSING_VALUE_FACTOR
		if( DESC_STATS_ON_ROWS != nOption )
		{
			///Kyle 08/07/2015 ORG-12921-P1 STATS_ON_COL_SKIP_EMPTY_OUTPUT_PLOTS
			//if( (OEXEM_ON_AUTOUPDATE_MANUAL == nExeMode || OEXEM_ON_AUTOUPDATE_TASK == nExeMode) && !trOp.GUI.InputData.Range1.F.IsEmpty() )
			if( (OEXEM_ON_AUTOUPDATE_MANUAL == nExeMode || OEXEM_ON_AUTOUPDATE_TASK == nExeMode) && (DescStatsExcludeEmptyDataset(trOp) || !trOp.GUI.InputData.Range1.F.IsEmpty()) )
			///End STATS_ON_COL_SKIP_EMPTY_OUTPUT_PLOTS
			{
				trOp.GUI.Output.SetAttribute(STR_RESET_GRAPH_ATTRIB, 1);
			}
		}
		///End KEEP_MISSING_VALUE_FACTOR
			
		if( DESC_STATS_ON_ROWS != nOption) 
/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifndef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH		
			return WksReportOperation::CalcMultiData(trOp, dr, nTotalNumData, nExeMode,dwExecCntrl);
#else	
		{			
			bool bRet = WksReportOperation::CalcMultiData(trOp, dr, nTotalNumData, nExeMode,dwExecCntrl);
			///------ Folger 03/31/2015 ORG-12824-S1 ALLOW_REMOVE_SHEET_OUTPUT_FROM_OPERATION
			//FilterStatsReport(trOp.GUI.Quantities, trOp.ResidualCurves.FlatOut);
			//SetTree(trOp);
			TreeNode trFlatOut = trOp.ResidualCurves.FlatOut;
			if (trFlatOut)
			{
				FilterStatsReport(trOp.GUI.Quantities, trFlatOut);
				SetTree(trOp);
			}
			///------ End ALLOW_REMOVE_SHEET_OUTPUT_FROM_OPERATION
			return bRet;
		}
#endif // __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX

		///------ Folger 07/10/2020 ORG-21828-P2 STATS_ON_ROWS_FAILED_TO_CONVERT_OP_ESCAPED_STRING
		/////------ Folger 05/12/2020 ORG-21897-P1 STATS_ON_ROWS_FAILED_ON_CONTINUOUS_DATA_SELECTED_ONE_BY_ONE
		//SetTree(trOp);
		/////------ End STATS_ON_ROWS_FAILED_ON_CONTINUOUS_DATA_SELECTED_ONE_BY_ONE
		
		/////------ Folger 11/27/2017 ORG-17439-S1 BETTER_INPUT_ERROR_CHECKING_FOR_STATS_ON_ROWS
		//bool	bIsContiguousRange = dr.ConvertToContiguous();
		/////------ End BETTER_INPUT_ERROR_CHECKING_FOR_STATS_ON_ROWS
		DataRange dr2;
		dr.Clone(dr2);
		bool	bIsContiguousRange = dr2.ConvertToContiguous();
		///------ End STATS_ON_ROWS_FAILED_TO_CONVERT_OP_ESCAPED_STRING

		TreeNode		trAdditionalData = tree_check_get_node(trOp,TREE_INPUTRANGE_ADDITIONAL_DATA_NODE_NAME); 
		DWORD			dwRules = GetDataRules(trOp);
		///------ Folger 07/10/2020 ORG-21828-P2 STATS_ON_ROWS_FAILED_TO_CONVERT_OP_ESCAPED_STRING
		//int 			nNumData = dr.GetNumData(dwRules, trAdditionalData);
		int 			nNumData = dr2.GetNumData(dwRules, trAdditionalData);
		///------ End STATS_ON_ROWS_FAILED_TO_CONVERT_OP_ESCAPED_STRING
		
		if(!checkStatsOnRowErr(nNumData))
			return false;
	
		///------ Folger 05/12/2020 ORG-21897-P1 STATS_ON_ROWS_FAILED_ON_CONTINUOUS_DATA_SELECTED_ONE_BY_ONE
		//SetTree(trOp);	
		///------ End STATS_ON_ROWS_FAILED_ON_CONTINUOUS_DATA_SELECTED_ONE_BY_ONE
		///------ Folger 07/10/2020 ORG-21828-P2 STATS_ON_ROWS_FAILED_TO_CONVERT_OP_ESCAPED_STRING
		SetTree(trOp);
		///------ End STATS_ON_ROWS_FAILED_TO_CONVERT_OP_ESCAPED_STRING
		
		/// Iris 2/22/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS
		/*
		matrix		mData;
		vector		vWeight;
		DWORD		ouidAux;
		vector<int>	vintRowIndices;
		Worksheet	wks;
		int			nn = dr.GetData(dwRules, 0, &ouidAux, NULL, NULL, NULL, &mData, NULL, &vWeight,
		                               NULL, NULL, &wks, NULL, &vintRowIndices);
		if(nn < 0)
			return error_report("failed to GetData from input");		
		*/				
		matrix		mData;
		/// Iris 3/16/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
		//vector<int>	vintRowIndices;		
		///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
		///------ Folger 11/27/2017 ORG-17439-S1 BETTER_INPUT_ERROR_CHECKING_FOR_STATS_ON_ROWS
		//bool	bIsContiguousRange = dr.ConvertToContiguous();
		///------ End BETTER_INPUT_ERROR_CHECKING_FOR_STATS_ON_ROWS
		if( bIsContiguousRange )
		{
			/// Iris 3/16/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
			/*
			int			nn = dr.GetData(dwRules, 0, NULL, NULL, NULL, NULL, &mData, NULL, NULL,
                               NULL, NULL, NULL, NULL, &vintRowIndices);
			if(nn < 0)
				return error_report("failed to GetData from input");
			*/
			matrix		mTemp;
			vector<int>	vintRowIndices;
			///------ Folger 07/10/2020 ORG-21828-P2 STATS_ON_ROWS_FAILED_TO_CONVERT_OP_ESCAPED_STRING
			//int			nn = dr.GetData(dwRules, 0, NULL, NULL, NULL, NULL, &mTemp, NULL, NULL,
			int			nn = dr2.GetData(dwRules, 0, NULL, NULL, NULL, NULL, &mTemp, NULL, NULL,
			///------ End STATS_ON_ROWS_FAILED_TO_CONVERT_OP_ESCAPED_STRING
			                               NULL, NULL, NULL, NULL, &vintRowIndices);
			if(nn < 0)
				return error_report("failed to GetData from input");
			
			///------ Folger 10/15/2020 ORG-22656-P1 STATS_ON_ROWS_FAILED_TO_SKIP_HIDDEN_ROWS
			//int r1 = vintRowIndices[0] - 1;
			Worksheet wks;
			int c1, c2;
			dr2.GetRange(wks, c1, c2);
			int r1 = vintRowIndices[0] - 1 - get_first_visible_row(wks);
			///------ End STATS_ON_ROWS_FAILED_TO_SKIP_HIDDEN_ROWS
			if( vintRowIndices.GetSize() > 0 && r1 > 0 ) // range not from 1st row
			{				
				mData.SetSize(r1 + mTemp.GetNumRows(), mTemp.GetNumCols());
				mData = NANUM;
				
				mData.SetSubMatrix(mTemp, 0, r1);
			}
			else
			{
				mData = mTemp;
			}			
			///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
		}
		else
		{
			///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
			TreeNode trGroup = trOp.GUI.InputData.Range1.F;
			if(trGroup && !trGroup.strVal.IsEmpty() && !compare_string_localization(trGroup.strVal, STR_OPTIONAL))
				return CalcMultiGroupRowData(trOp, dr);
			///End STATS_ON_ROWS_SUPPORT_GROUPING
			
			/// Iris 3/16/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
			/*
			int nNumRanges = dr.GetNumRanges();
			int nNumCols = 0;
			for(int nRange = 0; nRange < nNumRanges; nRange++)
			{
				vector		vTemp;
				vector<int>	vintRowIndicesTemp;
				int			nn = dr.GetData(DRR_GET_MISSING | DRR_NO_FACTORS | DRR_NO_WEIGHTS, nRange, NULL, NULL, vTemp, NULL, NULL, NULL, NULL,
				                               NULL, NULL, NULL, NULL, &vintRowIndicesTemp);
				                               
				if( nn >= 0 && vTemp.GetSize() > 0 )
				{
					nNumCols++;
					if( 0 == nRange )
					{
						vintRowIndices = vintRowIndicesTemp;
						mData.SetSize(vintRowIndices.GetSize(), nNumRanges);
					}
					
					if( 0 == nRange	|| vintRowIndicesTemp.GetSize() == vintRowIndices.GetSize() && vintRowIndicesTemp.GetSize() > 0 
						&& vintRowIndicesTemp[0] == vintRowIndices[0] )
					{					
						mData.SetColumn(vTemp, nRange);
					}
				}
			}
			if( nNumCols <= 0 )
				return error_report("failed to GetData from input");
			
			if( nNumCols < nNumRanges ) // may exist empty range string in DataRange obj
				mData.SetSize(vintRowIndices.GetSize(), nNumCols, true);
			*/
			if(!get_data_from_dr_to_mat(dr, mData, MATRIX_FROM_RANGE_REMOVE_MISSING_FROM_LAST_SEL_ROW))
				return error_report("failed to GetData from input");
			///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
		}
		/// Iris 3/16/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
		//CalcOneDataOnRow(trOp, mData, vintRowIndices);
		///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
		//CalcOneDataOnRow(trOp, mData);
		string strCommonUnit;
		getInputCommonUnit(strCommonUnit);
		CalcOneDataOnRow(trOp, mData, strCommonUnit);
		///End ADD_UNITS_TO_STATISTICS_ON_ROWS
		///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
		///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS

		
		return true;
	}
	
	///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
	//just for stats on row
	bool CalcMultiGroupRowData(TreeNode& trOp, DataRange& dr)
	{
		///------ Folger 10/21/2020 ORG-22656-P4 STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
		//vector<int> vnRows;
		///------ End STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
		int nRows = 0;
		int r1, c1, r2, c2, nMatRows = 0, nRanges = dr.GetNumRanges();
		Worksheet wks;
		string strName;
		///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
		vector<int> vnFactorRows;
		///End ADD_UNITS_TO_STATISTICS_ON_ROWS
		///------ Folger 10/21/2020 ORG-22656-P4 STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
		DWORD 	dwRules = GetDataRules(trOp);
		///------ End STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
		for(int nn = 0; nn < nRanges; nn++)
		{
			dr.GetRange(nn, r1, c1, r2, c2, wks, &strName);
			if( strcmp(strName, "X") == 0 )
			{
				///------ Folger 10/21/2020 ORG-22656-P4 STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
				//int nBoundR1, nBoundR2;
				//if( r2 == -1 && wks.GetBounds(nBoundR1, c1, nBoundR2, c2) )
					//r2 = nBoundR2;
				//if(r2 + 1 > nMatRows)
					//nMatRows = r2 + 1;
				//
				//vector<int> vTemp;
				//vTemp.Data(r1, r2, 1);
				//vnRows.Append(vTemp);
				matrix mTemp;
				vector<int> vintRowIndices;
				int nn = dr.GetData(dwRules, 0, NULL, NULL, NULL, NULL, &mTemp, NULL, NULL,
			                               NULL, NULL, NULL, NULL, &vintRowIndices);
			    nRows += vintRowIndices.GetSize();
				///------ End STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
			}
			///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
			if( strcmp(strName, "F") == 0 )
			{
				vnFactorRows.Add(r1);
			}
			///End ADD_UNITS_TO_STATISTICS_ON_ROWS
		}
		///------ Folger 10/21/2020 ORG-22656-P4 STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
		//int nRows = vnRows.GetSize();
				
		//DWORD 	dwRules = GetDataRules(trOp);
		nMatRows = nRows;
		///------ End STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
		int		nDatas = dr.GetNumData(dwRules);
		
		vector<int> vnGroups;
		vector<string> vsFactorValues;
		///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
		vector<string> vsCommonUnits;
		dr.GetRange(0, r1, c1, r2, c2, wks, &strName);
		///End ADD_UNITS_TO_STATISTICS_ON_ROWS
		for(int ii = 0; ii < nDatas; ii++)
		{
			vector<string> vsFactors;
			dr.GetFactorsValues(dwRules, ii, &vsFactors);
			string strFactors = str_combine(vsFactors, STR_TOKEN_SEP);
			if(vsFactorValues.Find(strFactors) < 0)
			{
				vsFactorValues.Add(strFactors);
				vnGroups.Add(ii);
				///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
				string strCommonUnits = "";
				for (int jj = c1; jj <= c2; jj++)
				{
					string strColFactors = "";
					int nLabelType;
					for (int kk = 0; kk < vnFactorRows.GetSize(); kk++)
					{
						nLabelType = wks.GetLabelType(vnFactorRows[kk]);
						string strLabel;
						wks.Columns(jj).GetExtendedLabel(strLabel, nLabelType);
						if (kk == 0)
							strColFactors = strLabel;
						else
							strColFactors = strColFactors + STR_TOKEN_SEP + strLabel;
					}
					if (strFactors == strColFactors)
					{
						string strConsistentUnit = wks.Columns(jj).GetUnits();
						if (strConsistentUnit == "")
						{
							strCommonUnits = "";
							break;
						}
						if (strCommonUnits == "")
							strCommonUnits = strConsistentUnit;
						else
							if (strcmp(strCommonUnits, strConsistentUnit) != 0)
							{
								strCommonUnits = "";
								break;
							}
					}
				}
				vsCommonUnits.Add(strCommonUnits);
				///End ADD_UNITS_TO_STATISTICS_ON_ROWS
			}
			else
				break;
		}
		
		int nGroups = vnGroups.GetSize();
		ASSERT(nDatas/nGroups == nRows);
		for(int nGroup = 0; nGroup < nGroups; nGroup++)
		{
			matrix mData;
			for(int nMatCols = 0, rr = 0; rr < nRows; rr++)
			{
				int nIndex = rr * nGroups + vnGroups[nGroup];
				vector vData;
				vector<string> vsFactors;
				vector<int> vnRowsInSource;
				Worksheet wksTemp;
				int	nRet = dr.GetData(dwRules, nIndex, NULL, NULL, &vData, NULL, NULL, &vsFactors, NULL, NULL, NULL, &wksTemp, NULL, &vnRowsInSource);
				ASSERT( lstrcmp(vsFactorValues[nGroup], str_combine(vsFactors, STR_TOKEN_SEP)) == 0 );
				
				if(nMatCols == 0)
				{
					nMatCols = vData.GetSize();
					mData.SetSize(nMatRows, nMatCols);
					mData = NANUM;
				}
				if(nMatRows > 0 && nMatCols > 0)
					///------ Folger 10/21/2020 ORG-22656-P4 STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
					//mData.SetRow(vData, vnRows[rr]);
					mData.SetRow(vData, rr);
					///------ End STATS_ON_ROWS_FAILED_TO_IGNORE_HIDDEN_ROWS_WHEN_GROUPING
			}
			///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
			//bool bRet = CalcOneDataOnRow(trOp, mData, nGroup);
			bool bRet = CalcOneDataOnRow(trOp, mData, vsCommonUnits[nGroup], nGroup);
			///End ADD_UNITS_TO_STATISTICS_ON_ROWS
		}
		
		return true;
	}
	///End STATS_ON_ROWS_SUPPORT_GROUPING
	
	//just for stats on row
	/// Iris 3/16/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
	//bool	CalcOneDataOnRow(TreeNode& trOp, matrix& mData, vector<int>& vintRowIndices)
	///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
	//bool	CalcOneDataOnRow(TreeNode& trOp, matrix& mData, int nGroup = 0)//bool	CalcOneDataOnRow(TreeNode& trOp, matrix& mData)///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
	bool	CalcOneDataOnRow(TreeNode& trOp, matrix& mData, string strCommonUnit, int nGroup = 0)
	///End ADD_UNITS_TO_STATISTICS_ON_ROWS
	///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
	{
		int nRows = mData.GetNumRows(), nCols = mData.GetNumCols();
		
		TreeNode trVarDivisor = trOp.GUI.Computation.VarDivisor;
		if(!trVarDivisor)
			return false;
		
		//Moments
		TreeNode trMoments = trOp.GUI.Quantities.Moments;
		if(!trMoments)
			return false;
		
		bool bComputeMoments = false; //check if need to compute Moments
		///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		//if(trMoments.Mean.nVal || trMoments.N.nVal || trMoments.SD.nVal || trMoments.SEM.nVal
		//	 || trMoments.LCL.nVal || trMoments.UCL.nVal || trMoments.Sum.nVal)
		if(trMoments.N.nVal || trMoments.Missing.nVal || trMoments.Mean.nVal
			 || trMoments.SD.nVal || trMoments.SEM.nVal || trMoments.LCL.nVal
			 || trMoments.UCL.nVal || trMoments.Variance.nVal || trMoments.Sum.nVal
			 || trMoments.Skewness.nVal || trMoments.Kurtosis.nVal || trMoments.UncorSumSq.nVal
			 || trMoments.CorSumSq.nVal || trMoments.COV.nVal || trMoments.MAD.nVal
			 || trMoments.SDx2.nVal || trMoments.SDx3.nVal || trMoments.GeoMean.nVal
			 || trMoments.GeoSD.nVal || trMoments.Mode.nVal
			 /// Ziv 02/08/2017 ORG-14788-S1 DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
			 || trMoments.HarmonicMean.nVal
			 /// End DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
			 )	 
		///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
			bComputeMoments = true;
		
		vector vMean(nRows), vSd(nRows), vSem(nRows), vMin(nRows), vMax(nRows), vSum(nRows),
				vN(nRows), vLCL(nRows), vUCL(nRows);
		///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		//if(bComputeMoments && ocmath_row_desc_stats(nRows, nCols, mData, vMean, vSd, vSem, vMin, vMax, vSum, vN, vLCL, vUCL, trVarDivisor.nVal))
		//{
			//string strErr;
			//if( ocu_load_err_msg_str(CER_FAILED_GET_MOMENTS, &strErr) )
				//okoc_out_msg(strErr);
		//}
		vector vVariance(nRows), vSkewness(nRows), vKurtosis(nRows),
				vUncorSumSq(nRows), vCorSumSq(nRows), vCOV(nRows), vMAD(nRows), 
				vSDx2(nRows), vSDx3(nRows), vGeoMean(nRows), vGeoSD(nRows), vMode(nRows),
				/// Ziv 02/08/2017 ORG-14788-S1 DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
				vHarmonicMean(nRows);
				/// End DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
		vector<int> vnMissing(nRows);
		vector *pMean = NULL, *pSd = NULL, *pSem = NULL, *pSum = NULL, *pN = NULL, 
				*pLCL = NULL, *pUCL = NULL, *pVariance = NULL, *pSkewness = NULL, 
				*pKurtosis = NULL, *pUncorSumSq = NULL, *pCorSumSq = NULL, *pCOV = NULL, 
				*pMAD = NULL, *pSDx2 = NULL, *pSDx3 = NULL, *pGeoMean = NULL, *pGeoSD = NULL, *pMode = NULL,
				/// Ziv 02/08/2017 ORG-14788-S1 DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
				*pHarmonicMean = NULL;
				/// End DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
		vector<int>* pMissing = NULL;
		if(trMoments.N.nVal) pN = &vN;
		if(trMoments.Missing.nVal) pMissing = &vnMissing;
		if(trMoments.Mean.nVal) pMean = &vMean;
		if(trMoments.SD.nVal) pSd = &vSd;
		if(trMoments.SEM.nVal) pSem = &vSem;
		if(trMoments.LCL.nVal) pLCL = &vLCL;
		if(trMoments.UCL.nVal) pUCL = &vUCL;
		if(trMoments.Variance.nVal) pVariance = &vVariance;
		if(trMoments.Sum.nVal) pSum = &vSum;
		if(trMoments.Skewness.nVal) pSkewness = &vSkewness;
		if(trMoments.Kurtosis.nVal) pKurtosis = &vKurtosis;
		if(trMoments.UncorSumSq.nVal) pUncorSumSq = &vUncorSumSq;
		if(trMoments.CorSumSq.nVal) pCorSumSq = &vCorSumSq;
		if(trMoments.COV.nVal) pCOV = &vCOV;
		if(trMoments.SDx2.nVal) pSDx2 = &vSDx2;
		if(trMoments.SDx3.nVal) pSDx3 = &vSDx3;
		if(trMoments.MAD.nVal) pMAD = &vMAD;
		if(trMoments.GeoMean.nVal) pGeoMean = &vGeoMean;
		if(trMoments.GeoSD.nVal) pGeoSD = &vGeoSD;
		if(trMoments.Mode.nVal) pMode = &vMode;
		/// Ziv 02/08/2017 ORG-14788-S1 DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
		if(trMoments.HarmonicMean.nVal) pHarmonicMean = &vHarmonicMean;
		/// End DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
		if(bComputeMoments)
		{
			if(ocmath_row_desc_stats_ex(nRows, nCols, mData, *pMean, *pSd,  
						*pSem, NULL, NULL, *pSum, *pN, *pLCL, *pUCL, *pVariance,
						*pSkewness, *pKurtosis, *pUncorSumSq, *pCorSumSq, *pCOV, *pMAD, *pMissing, *pGeoMean, 
						*pMode, NULL, *pGeoSD, *pSDx2, *pSDx3, trVarDivisor.nVal,
						/// Ziv 02/08/2017 ORG-14788-S1 DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
						*pHarmonicMean
						/// End DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
						) )
			{
				string strErr;
				if( ocu_load_err_msg_str(CER_FAILED_GET_MOMENTS, &strErr) )
					okoc_out_msg(strErr);
			}	
		}
		///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		
		TreeNode trInterpolate = trOp.GUI.Computation.Interpolate;
		if(!trInterpolate)
			return false;
		
		//Quantiles
		TreeNode trQuantiles = trOp.GUI.Quantities.Quantiles;
		if(!trQuantiles)
			return false;
		
		bool bComputeQuantiles = false; //check if need to compute Quantiles
		/// Max 07-11-17 NEED_TO_CHECK_CUSTOMPERCENTILES_NODE
		/////Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		////if(trQuantiles.Min.nVal || trQuantiles.Q1.nVal || trQuantiles.Median.nVal 
		////		|| trQuantiles.Q3.nVal || trQuantiles.Max.nVal)
		//if(trQuantiles.Min.nVal || trQuantiles.Q1.nVal || trQuantiles.Median.nVal 
				//|| trQuantiles.Q3.nVal || trQuantiles.Max.nVal || trQuantiles.iMin.nVal
				//|| trQuantiles.iMax.nVal || trQuantiles.IQR.nVal || trQuantiles.Range.nVal || trQuantiles.PercentileList.nVal)		
		/////end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		if(trQuantiles.Min.nVal || trQuantiles.Q1.nVal || trQuantiles.Median.nVal 
				|| trQuantiles.Q3.nVal || trQuantiles.Max.nVal || trQuantiles.iMin.nVal
				|| trQuantiles.iMax.nVal || trQuantiles.IQR.nVal || trQuantiles.Range.nVal || (trQuantiles.CustomPercentiles.nVal && trQuantiles.PercentileList.nVal)
				/// Ziv 02/13/2017 ORG-14789-S1 DESCSTATS_SUPPORT_MAD_RCV
				|| trQuantiles.MedianAD.nVal || trQuantiles.RCV.nVal
				/// End DESCSTATS_SUPPORT_MAD_RCV
				)
		/// END NEED_TO_CHECK_CUSTOMPERCENTILES_NODE
			bComputeQuantiles = true;
			
		vector vQ1(nRows), vMedian(nRows), vQ3(nRows);
		///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		//if(bComputeQuantiles && ocmath_row_quantiles(nRows, nCols, mData, vMin, vMax, vQ1, vMedian, vQ3, trInterpolate.nVal) )
		//{
			//string strErr;
			//if( ocu_load_err_msg_str(CER_FAILED_GET_QUANTITIES, &strErr) )
				//okoc_out_msg(strErr);
		//}
		/// Ziv 02/13/2017 ORG-14789-S1 DESCSTATS_SUPPORT_MAD_RCV
		vector vMedianAD(nRows), vRCV(nRows);
		/// End DESCSTATS_SUPPORT_MAD_RCV
		vector vIQR(nRows), vRange(nRows), vPercents, vPercentiles;
		vector<int> vniMin(nRows), vniMax(nRows);
		vector *pQ1 = NULL, *pMedian = NULL, *pQ3 = NULL, *pIQR = NULL, 
				*pRange = NULL, *pMin = NULL, *pMax =NULL, *pMatPercentiles = NULL,
				/// Ziv 02/13/2017 ORG-14789-S1 DESCSTATS_SUPPORT_MAD_RCV
				*pMedianAD = NULL, *pRCV = NULL;
				/// End DESCSTATS_SUPPORT_MAD_RCV
		vector<int> *piMin = NULL, *piMax = NULL;
		bool *pShow = NULL;
		vector<bool> vbShow;
		double *pPercents = NULL; 
		if(trQuantiles.Min.nVal) pMin = &vMin;
		if(trQuantiles.Max.nVal) pMax = &vMax;
		if(trQuantiles.Q1.nVal) pQ1 = &vQ1;
		if(trQuantiles.Median.nVal) pMedian = &vMedian;
		if(trQuantiles.Q3.nVal) pQ3 = &vQ3;
		if(trQuantiles.iMin.nVal) piMin = &vniMin;
		if(trQuantiles.iMax.nVal) piMax = &vniMax;
		if(trQuantiles.IQR.nVal) pIQR = &vIQR;
		if(trQuantiles.Range.nVal) pRange = &vRange;
		/// Ziv 02/13/2017 ORG-14789-S1 DESCSTATS_SUPPORT_MAD_RCV
		if(trQuantiles.MedianAD.nVal) pMedianAD = &vMedianAD;
		if(trQuantiles.RCV.nVal) pRCV = &vRCV;
		/// End DESCSTATS_SUPPORT_MAD_RCV
		
		uint nPercentsSize = 0;
		if(trQuantiles.CustomPercentiles.nVal)
		{
			string strCustomPercents = trQuantiles.PercentileList.strVal;
			vector<bool> vShow;
			GetPercentsForPercentiles(trOp, strCustomPercents, vPercents, vbShow);
			if(vbShow.GetSize() != vPercents.GetSize() )
				return false;
			pPercents = vPercents;
			nPercentsSize = vPercents.GetSize();
			vPercentiles.SetSize(nRows*nPercentsSize);
			pMatPercentiles = &vPercentiles;
			pShow = vbShow;
		}
		
		if(bComputeQuantiles)
		{
			if( ocmath_row_quantiles_ex(nRows, nCols, mData, *pMin, *pMax, *pQ1, *pMedian, *pQ3, 
				*piMin, *piMax, *pIQR, *pRange, pPercents, nPercentsSize, *pMatPercentiles, trInterpolate.nVal,
				/// Ziv 02/13/2017 ORG-14789-S1 DESCSTATS_SUPPORT_MAD_RCV
				*pMedianAD, *pRCV) )
				/// End DESCSTATS_SUPPORT_MAD_RCV
			{
				string strErr;
				if( ocu_load_err_msg_str(CER_FAILED_GET_QUANTITIES, &strErr) )
					okoc_out_msg(strErr);
			}
			if(piMin) *piMin += 1;
			if(piMax) *piMax += 1;
		}
		///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		
		///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		////if no out put, not need to do computing and add result
		//bool bRet = true;
		//if(bComputeMoments || bComputeQuantiles)
			//bRet = AddDescStatsTableOnRow(trOp, vintRowIndices, vMean, vSd, vSem, vMin, vMax, 
				//vSum, vN, vLCL, vUCL, vQ1, vMedian, vQ3) ;
				//
		//return bRet;
		//support insert row
		/// Iris 3/16/2010 QA81-10824 SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
		/*
		vector		vtemp(vintRowIndices[vintRowIndices.GetSize() - 1]);
		vtemp		= NANUM;
		int 		nInsertCol = vintRowIndices[0] - 1;
		*/
		vector		vtemp(mData.GetNumRows());
		vtemp		= NANUM;
		int			nInsertCol = 0;
		///End SUPPORT_NON_CONTIGUOUS_RANGES_FOR_STATS_ON_ROWS_MORE
		///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
		//TreeNode	trTable 	= tree_check_get_node(trOp.Calculation, TABLE_DESC_STATS, IDST_DESC_STATS_RESULTS, STR_LABEL_ATTRIB, OUTPUT_DESC_STATS);
		string 		strName = nGroup > 0? TABLE_DESC_STATS+nGroup : TABLE_DESC_STATS;
		TreeNode	trTable = tree_check_get_node(trOp.Calculation, strName, IDST_DESC_STATS_RESULTS+nGroup, STR_LABEL_ATTRIB, OUTPUT_DESC_STATS);		
		///End STATS_ON_ROWS_SUPPORT_GROUPING
		///------ Folger 03/24/10 QA81-15224 STATS_ON_ROWS_FAILED_TO_UPDATE_COL_HEADERS_WHEN_RECALCULATE
		///------ Folger 08/02/2012 ORG-6412-S1 XF_REPORT_DATA_SET_COLUMN_SHORT_NAME_CONTROL
		//trTable.SetAttribute(STR_REPORT_TREE_ALWAYS_UPDATE_COLUMN_LABELS_ATTRIB, 1);
		trTable.SetAttribute(STR_REPORT_TREE_SETGRTR_ATTRIB, SETGRTR_ALWAYS_UPDATE_COLUMN_LABELS);
		///------ End XF_REPORT_DATA_SET_COLUMN_SHORT_NAME_CONTROL
		///------ End STATS_ON_ROWS_FAILED_TO_UPDATE_COL_HEADERS_WHEN_RECALCULATE
		int 		nID			= IDST_TEMP_ONE_SET;
		
		
		if(bComputeMoments)
		{
			if( !AddDescStatsTableOnRowMoments(trTable, vtemp, nInsertCol, nID,
					///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
					strCommonUnit,
					///End ADD_UNITS_TO_STATISTICS_ON_ROWS
					pMean, pSd, pSem, pSum, pN, pLCL, pUCL, pVariance, pSkewness, 
					pKurtosis, pUncorSumSq, pCorSumSq, pCOV, pMAD, pMissing, pGeoMean, pMode, pGeoSD, pSDx2, pSDx3,
					/// Ziv 02/08/2017 ORG-14788-S1 DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
					pHarmonicMean) )
					/// End DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
				return error_report("failed to add Moments to report table for StatsOnRow");
		}
		if(bComputeQuantiles)
		{
			if( !AddDescStatsTableOnRowQuantiles(trTable, vtemp, nInsertCol, nID,
					///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
					strCommonUnit,
					///End ADD_UNITS_TO_STATISTICS_ON_ROWS
					pMin, pMax, pQ1, pMedian, pQ3, piMin, piMax, pIQR, pRange, nRows, nPercentsSize, pPercents, pShow, pMatPercentiles,
					/// Ziv 02/13/2017 ORG-14789-S1 DESCSTATS_SUPPORT_MAD_RCV
					pMedianAD, pRCV) )
				/// End DESCSTATS_SUPPORT_MAD_RCV
				return error_report("failed to add Quantiles to report table for StatsOnRow");
		}
		///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		return true;
	}
	
	///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
	////just for stats on row
	//bool 	AddDescStatsTableOnRow(TreeNode& trOp, const vector<int>& vintRowIndices,
				//const vector& vMean, const vector& vSd, const vector& vSem, const vector& vMin, 
				//const vector& vMax, const vector& vSum, const vector& vN, const vector& vLCL, 
				//const vector& vUCL, const vector& vQ1, const vector& vMedian, const vector& vQ3) 
	//{
		////support insert row
		//vector		vtemp(vintRowIndices[vintRowIndices.GetSize() - 1]);
		//vtemp		= NANUM;
		//int 		nInsertCol = vintRowIndices[0] - 1;
		//
		//TreeNode	trTable 	= tree_check_get_node(trOp.Calculation, TABLE_DESC_STATS, IDST_DESC_STATS_RESULTS, STR_LABEL_ATTRIB, _L("Descriptive Statistics"));		
		//int 		nID			= IDST_TEMP_ONE_SET;
		//TreeNode	trRow;
		//
		/////Cheney 2007-6-7 CLEAN_UP_OWN_CODE
		////N
		//addDestStatsOnRowsOneResult(trTable, "N", nID, STR_DESC_STATIS_GUI_LABEL_SAMPLE_SIZE, IDE_SAMPLE_SIZE, vN, nInsertCol, vtemp);
		//
		////Mean
		//addDestStatsOnRowsOneResult(trTable, "Mean", nID, STR_DESC_STATIS_GUI_LABEL_MEAN, IDE_MEAN, vMean, nInsertCol, vtemp);
		//
		////SD
		/////Arvin 08/31/07 QA70-7651-P17 WRONG_COLUMN_DESIGNATION_TYPE
		////addDestStatsOnRowsOneResult(trTable, "SD", nID, STR_DESC_STATIS_GUI_LABEL_SD, IDE_SD, vSd, nInsertCol, vtemp);
		//addDestStatsOnRowsOneResult(trTable, "SD", nID, STR_DESC_STATIS_GUI_LABEL_SD, IDE_SD, vSd, nInsertCol, vtemp, OKDATAOBJ_DESIGNATION_ERROR);
		/////end WRONG_COLUMN_DESIGNATION_TYPE
		//
		////SEM
		/////Arvin 08/31/07 QA70-7651-P17 WRONG_COLUMN_DESIGNATION_TYPE
		////addDestStatsOnRowsOneResult(trTable, "SEM", nID, STR_DESC_STATIS_GUI_LABEL_SEM, IDE_SEM, vSem, nInsertCol, vtemp);
		//addDestStatsOnRowsOneResult(trTable, "SEM", nID, STR_DESC_STATIS_GUI_LABEL_SEM, IDE_SEM, vSem, nInsertCol, vtemp, OKDATAOBJ_DESIGNATION_ERROR);
		/////end WRONG_COLUMN_DESIGNATION_TYPE
		//
		////LCL
		//addDestStatsOnRowsOneResult(trTable, "LCL", nID, STR_DESC_STATIS_GUI_LABEL_LCL, IDE_LCL, vLCL, nInsertCol, vtemp);
			//
		////UCL
		//addDestStatsOnRowsOneResult(trTable, "UCL", nID, STR_DESC_STATIS_GUI_LABEL_UCL, IDE_UCL, vUCL, nInsertCol, vtemp);
		//
		////Sum
		//addDestStatsOnRowsOneResult(trTable, "Sum", nID, STR_DESC_STATIS_GUI_LABEL_SUM, IDE_SUM, vSum, nInsertCol, vtemp);
//
		////Min
		//addDestStatsOnRowsOneResult(trTable, "Min", nID, STR_DESC_STATIS_GUI_LABEL_MIN, IDE_MIN, vMin, nInsertCol, vtemp);
		//
		////Q1
		//addDestStatsOnRowsOneResult(trTable, "Q1", nID, STR_DESC_STATIS_GUI_LABEL_P25, IDE_P25, vQ1, nInsertCol, vtemp);
		//
		////Median
		//addDestStatsOnRowsOneResult(trTable, "Median", nID, STR_DESC_STATIS_GUI_LABEL_MEDIAN, IDE_MEDIAN, vMedian, nInsertCol, vtemp);
		//
		////Q3
		//addDestStatsOnRowsOneResult(trTable, "Q3", nID, STR_DESC_STATIS_GUI_LABEL_P75, IDE_P75, vQ3, nInsertCol, vtemp);
		//
		////Max
		//addDestStatsOnRowsOneResult(trTable, "Max", nID, STR_DESC_STATIS_GUI_LABEL_MAX, IDE_MAX, vMax, nInsertCol, vtemp);
		/////end CLEAN_UP_OWN_CODE
		//
		//return true;
	//}
	bool 	AddDescStatsTableOnRowMoments(TreeNode& trTable, vector& vec, int nInsertCol, int& nID,
				///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
				string strInputUnit,
				///End ADD_UNITS_TO_STATISTICS_ON_ROWS
				const vector* pMean = NULL, const vector* pSd = NULL, const vector* pSem = NULL, 
				const vector* pSum = NULL, const vector* pN = NULL, const vector* pLCL = NULL, 
				const vector* pUCL = NULL, const vector* pVariance = NULL, const vector* pSkewness = NULL, 
				const vector* pKurtosis = NULL, const vector* pUncorSumSq = NULL, 
				const vector* pCorSumSq = NULL, const vector* pCOV = NULL, const vector* pMAD = NULL, 
				const vector<int>* pMissing = NULL, const vector* pGeoMean = NULL, const vector* pMode = NULL, 
				const vector* pGeoSD = NULL, const vector* pSDx2 = NULL, const vector* pSDx3 = NULL,
				/// Ziv 02/08/2017 ORG-14788-S1 DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
				const vector* pHarmonicMean = NULL
				/// End DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
				)
	{
		///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
		string strNoUnit = "";
		string strSqrUnit = "";
		if (strInputUnit != "")
			strSqrUnit = strInputUnit + "^2";
		///End ADD_UNITS_TO_STATISTICS_ON_ROWS
		
		//N
		checkAddDestStatsOnRowsOneResult(trTable, "N", nID, strNoUnit, STR_DESC_STATIS_GUI_LABEL_SAMPLE_SIZE, pN, nInsertCol, vec, IDE_SAMPLE_SIZE);

		//Missing
		checkAddDestStatsOnRowsOneResult(trTable, "Missing", nID, strNoUnit, STR_DESC_STATIS_GUI_LABEL_NUM_MISSING, pMissing, nInsertCol, vec, IDE_NUM_MISSING);

		//Mean
		checkAddDestStatsOnRowsOneResult(trTable, "Mean", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_MEAN, pMean, nInsertCol, vec, IDE_MEAN);
		
		//SD
		checkAddDestStatsOnRowsOneResult(trTable, "SD", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_SD, pSd, nInsertCol, vec, IDE_SD, OKDATAOBJ_DESIGNATION_ERROR);
		
		//SEM
		checkAddDestStatsOnRowsOneResult(trTable, "SEM", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_SEM, pSem, nInsertCol, vec, IDE_SEM, OKDATAOBJ_DESIGNATION_ERROR);
			
		//LCL
		checkAddDestStatsOnRowsOneResult(trTable, "LCL", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_LCL, pLCL, nInsertCol, vec, IDE_LCL);
			
		//UCL
		checkAddDestStatsOnRowsOneResult(trTable, "UCL", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_UCL, pUCL, nInsertCol, vec, IDE_UCL);
		
		//Variance
		checkAddDestStatsOnRowsOneResult(trTable, "Variance", nID, strSqrUnit, STR_DESC_STATIS_GUI_LABEL_VARIANCE, pVariance, nInsertCol, vec, IDE_VARIANCE);
		
		//Sum
		checkAddDestStatsOnRowsOneResult(trTable, "Sum", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_SUM, pSum, nInsertCol, vec, IDE_SUM);
		
		//Skewness
		checkAddDestStatsOnRowsOneResult(trTable, "Skewness", nID, strNoUnit, STR_DESC_STATIS_GUI_LABEL_SKEWNESS, pSkewness, nInsertCol, vec, IDE_SKEWNESS);
		
		//Kurtosis
		checkAddDestStatsOnRowsOneResult(trTable, "Kurtosis", nID, strNoUnit, STR_DESC_STATIS_GUI_LABEL_KURTOSIS, pKurtosis, nInsertCol, vec, IDE_KURTOSIS);
		
		//UncorSumSq
		checkAddDestStatsOnRowsOneResult(trTable, "UncorSumSq", nID, strSqrUnit, STR_DESC_STATIS_GUI_LABEL_UNCORSUMSQ, pUncorSumSq, nInsertCol, vec, IDE_UNCORSUMSQ);
		
		//CorSumSq
		checkAddDestStatsOnRowsOneResult(trTable, "CorSumSq", nID, strSqrUnit, STR_DESC_STATIS_GUI_LABEL_CORSUMSQ, pCorSumSq, nInsertCol, vec, IDE_CORSUMSQ);
		
		//COV
		checkAddDestStatsOnRowsOneResult(trTable, "COV", nID, strNoUnit, STR_DESC_STATIS_GUI_LABEL_COV, pCOV, nInsertCol, vec, IDE_COV);
		
		//MAD
		///Sophy 4/3/2009 QA80-13352 SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
		//checkAddDestStatsOnRowsOneResult(trTable, "MAD", nID, STR_DESC_STATIS_GUI_LABEL_MAD, pMAD, nInsertCol, vec, IDE_MAD);
		checkAddDestStatsOnRowsOneResult(trTable, "MAD", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_MAD, pMAD, nInsertCol, vec, IDE_MAD, OKDATAOBJ_DESIGNATION_ERROR);
		///end SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
		
		//SDx2
		///Sophy 4/3/2009 QA80-13352 SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
		//checkAddDestStatsOnRowsOneResult(trTable, "SDx2", nID, STR_DESC_STATIS_GUI_LABEL_SD_X_2, pSDx2, nInsertCol, vec, IDE_SD_X_2);
		checkAddDestStatsOnRowsOneResult(trTable, "SDx2", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_SD_X_2, pSDx2, nInsertCol, vec, IDE_SD_X_2, OKDATAOBJ_DESIGNATION_ERROR);
		///end SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
		
		//SDx3
		///Sophy 4/3/2009 QA80-13352 SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
		//checkAddDestStatsOnRowsOneResult(trTable, "SDx3", nID, STR_DESC_STATIS_GUI_LABEL_SD_X_3, pSDx3, nInsertCol, vec, IDE_SD_X_3);
		checkAddDestStatsOnRowsOneResult(trTable, "SDx3", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_SD_X_3, pSDx3, nInsertCol, vec, IDE_SD_X_3, OKDATAOBJ_DESIGNATION_ERROR);
		///end SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
		
		//GeoMean
		checkAddDestStatsOnRowsOneResult(trTable, "GeoMean", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_GEO_MEAN, pGeoMean, nInsertCol, vec, IDE_GEO_MEAN);
				
		//GeoSD
		///Sophy 4/3/2009 QA80-13352 SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
		//checkAddDestStatsOnRowsOneResult(trTable, "GeoSD", nID, STR_DESC_STATIS_GUI_LABEL_GEO_SD, pGeoSD, nInsertCol, vec, IDE_GEO_SD);
		checkAddDestStatsOnRowsOneResult(trTable, "GeoSD", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_GEO_SD, pGeoSD, nInsertCol, vec, IDE_GEO_SD, OKDATAOBJ_DESIGNATION_ERROR);
		///end SUPPORT_SPECIFY_COLUMN_DESIGNATIONS_IN_REPORT_TABLES
		
		//Mode
		checkAddDestStatsOnRowsOneResult(trTable, "Mode", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_MODE, pMode, nInsertCol, vec, IDE_MODE);

		/// Ziv 02/08/2017 ORG-14788-S1 DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN
		// Harmonic Mean
		checkAddDestStatsOnRowsOneResult(trTable, "HarmonicMean", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_HARMO_MEAN, pHarmonicMean, nInsertCol, vec, IDE_HARMO_MEAN);
		/// End DESCSTATS_ROW_SUPPORT_HARMONIC_MEAN

		return true;
	}
	
	bool 	AddDescStatsTableOnRowQuantiles(TreeNode& trTable, vector& vec, int nInsertCol, int& nID,
				///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
				string strInputUnit,
				///End ADD_UNITS_TO_STATISTICS_ON_ROWS
				const vector* pMin = NULL, const vector* pMax = NULL, const vector* pQ1 = NULL, 
				const vector* pMedian = NULL, const vector* pQ3 = NULL, const vector<int>* piMin = NULL, 
				const vector<int>* piMax = NULL, const vector* pIQR = NULL, const vector* pRange = NULL,
				uint nRows = 0, uint nPercentsSize = 0, const double* pPecents = NULL, bool* pShow = NULL, const vector* pMatPercentiles = NULL,
				/// Ziv 02/13/2017 ORG-14789-S1 DESCSTATS_SUPPORT_MAD_RCV
				const vector *pMedianAD = NULL, const vector *pRCV = NULL
				/// End DESCSTATS_SUPPORT_MAD_RCV
				)
	{
		///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
		string strNoUnit = "";
		string strSqrUnit = "";
		if (strInputUnit != "")
			strSqrUnit = strInputUnit + "^2";
		///End ADD_UNITS_TO_STATISTICS_ON_ROWS
		
		//Min
		checkAddDestStatsOnRowsOneResult(trTable, "Min", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_MIN, pMin, nInsertCol, vec, IDE_MIN);
		
		//iMin
		checkAddDestStatsOnRowsOneResult(trTable, "iMin", nID, strNoUnit, STR_DESC_STATIS_GUI_LABEL_IMIN, piMin, nInsertCol, vec, IDE_IMIN);

		//Q1
		checkAddDestStatsOnRowsOneResult(trTable, "Q1", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_P25, pQ1, nInsertCol, vec, IDE_P25);
		
		//Median
		checkAddDestStatsOnRowsOneResult(trTable, "Median", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_MEDIAN, pMedian, nInsertCol, vec, IDE_MEDIAN);
		
		//Q3
		checkAddDestStatsOnRowsOneResult(trTable, "Q3", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_P75, pQ3, nInsertCol, vec, IDE_P75);
		
		//Max
		checkAddDestStatsOnRowsOneResult(trTable, "Max", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_MAX, pMax, nInsertCol, vec, IDE_MAX);
		
		//iMax
		checkAddDestStatsOnRowsOneResult(trTable, "iMax", nID, strNoUnit, STR_DESC_STATIS_GUI_LABEL_IMAX, piMax, nInsertCol, vec, IDE_IMAX);
		
		//IQR
		checkAddDestStatsOnRowsOneResult(trTable, "IQR", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_IQR, pIQR, nInsertCol, vec, IDE_IQR);
		
		//Range
		checkAddDestStatsOnRowsOneResult(trTable, "Range", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_RANGE, pRange, nInsertCol, vec, IDE_RANGE);
		
		//Percentiles
		if(pMatPercentiles)
		{
			if( nRows < 1 || nPercentsSize < 1 || !pPecents || !pShow )
				return false;
			
			matrix mattemp;
			mattemp.SetSize(nRows, nPercentsSize);
			mattemp.SetByVector( *pMatPercentiles);
			
			for(int ii = 0; ii < nPercentsSize; ii++)
			{
				if(!pShow[ii])
					continue;
				
				vector vSub;
				mattemp.GetColumn( vSub, ii );
				string strTemp;
				double dPecents = pPecents[ii];
				strTemp.Format("P%s", ftoa(dPecents));
				checkAddDestStatsOnRowsOneResult(trTable, CALCULATION_PERCENTILE_PREFIX+(ii+1), IDE_CUSTOM_PERCENTILES + ii, strInputUnit, strTemp, &vSub, nInsertCol, vec, NULL, OKDATAOBJ_DESIGNATION_Y, true, &dPecents );
			}
		}

		/// Ziv 02/13/2017 ORG-14789-S1 DESCSTATS_SUPPORT_MAD_RCV
		// Median Absolute Deviation
		checkAddDestStatsOnRowsOneResult(trTable, "MedianAD", nID, strInputUnit, STR_DESC_STATIS_GUI_LABEL_MEDIAN_MAD, pMedianAD, nInsertCol, vec, IDE_MEDIAN_MAD);

		// Robust Coefficient of Variation
		checkAddDestStatsOnRowsOneResult(trTable, "RCV", nID, strNoUnit, STR_DESC_STATIS_GUI_LABEL_RCV, pRCV, nInsertCol, vec, IDE_RCV);
		/// End DESCSTATS_SUPPORT_MAD_RCV

		
		return true;
	}
	///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
	
 	//virtual 
 	TreeNode GetResultLogTree(TreeNode& trOp)
 	{ 
 		int 	nOption = trOp.GUI.StatsOnRows.nVal;
		if( DESC_STATS_ON_ROWS != nOption)
		/// Iris 3/26/2015 ORG-12836-S3 IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
		/*
/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifndef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH			
 			return trOp.Calculation;
#else
		{
			string strLabel;
			if( trOp.Calculation.GetAttribute(STR_LABEL_ATTRIB, strLabel) )
				trOp.ResidualCurves.SetAttribute(STR_LABEL_ATTRIB, strLabel);
			return trOp.ResidualCurves;
		}
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
		*/
			return trOp.Calculation;
		///End IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
		
		//if stats on row, should not out put any statistic result
		/// Iris 8/29/2011 ORG-3645-P1 FIX_STATS_ON_ROWS_FAIL_TO_OPEN_DLG
		// to fix stats on rows - Input Data table data range not be converted in Script window, Result Log and Notes window.
		/*
		TreeNode trNode = trOp.Calculation.Clone();
		TreeNode trStatistics = trNode.Statistics;
		if(trStatistics)
			trStatistics.Remove();
		return trNode;
		*/
		///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
		//TreeNode trStatistics = trOp.Calculation.Statistics;
		TreeNodeCollection tnc(trOp.Calculation, "Statistics");
		foreach(TreeNode trStatistics in tnc)
		{
		///End STATS_ON_ROWS_SUPPORT_GROUPING
		if( trStatistics )
			trStatistics.Show = false;
		}///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
		return trOp.Calculation;
		///End FIX_STATS_ON_ROWS_FAIL_TO_OPEN_DLG
 	}

 	/// Iris 8/22/2011 ORG-2427-S4 QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX
#ifdef __STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
	//virtual
	void SetOutputBookSheetDefaultName(TreeNode& trGUI)
	{
		StatsOpBase::SetOutputBookSheetDefaultName(trGUI);
		
		/// Iris 3/26/2015 ORG-12836-S3 IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
		//SetOneOutputBookSheetDefaultName(trGUI, trGUI.Output.FlatOut, true, "ColStatFlat1");	
		//SetOneOutputBookSheetDefaultName(trGUI, trGUI.Output.FlatOut, false, "DescStatsFlat1");
		SetOneOutputBookSheetDefaultName(trGUI, trGUI.Output.FlatOut, true, "ColStatQuantities1");	
		SetOneOutputBookSheetDefaultName(trGUI, trGUI.Output.FlatOut, false, "DescStatsQuantities1");
		///End IMPROVE_STATS_ON_COLS_OUTPUT_SETTINGS_PART_GUI
	}
#endif //__STATS_ON_COLS_SUPPORT_QUANTITIES_OUTPUT_BRANCH
	///End QUANTITIES_BOOKSHEET_BRANCH_REPLACE_CHECKBOX

	///------ Folger 06/06/2012 ORG-5906-P1 NORMALITY_TEST_TOO_SLOW_FOR_LARGE_DATA
	virtual void GetCalcMoment(TreeNode& trOp, DescStatOptions& opMoments)
	{
		TreeNode trMoment = trOp.GUI.Quantities.Moments;
		TreeNode trVarDivisor = trOp.GUI.Computation.VarDivisor;
		if ( trMoment && trVarDivisor )
		{
			opMoments = trMoment;
			opMoments.VarDivisor = trVarDivisor.nVal;
		}
		else
		{
			ASSERT(FALSE);
			InitMoments(opMoments);
		}
	}
	///------ End NORMALITY_TEST_TOO_SLOW_FOR_LARGE_DATA
	
private:
	bool checkStatsOnRowErr(int nErr)
	{
		string strErr;
		switch(nErr)
		{
		case EXTRACTBYROWSERR_MULTIPLE_SHEETS:
			///------ Folger 05/12/2020 ORG-21828-S1 STATS_ON_ROWS_SUPPORT_INPUT_FROM_DIFF_WKS
			//ocu_load_err_msg_str(CER_EXTRACTBYROWSERR_MULTIPLE_SHEETS, &strErr);
			nErr = 1;
			///------ End STATS_ON_ROWS_SUPPORT_INPUT_FROM_DIFF_WKS
			break;
		case EXTRACTBYROWSERR_UNEVEN_COLUMNS:
			///------ Folger 11/27/2017 ORG-17439-S1 BETTER_INPUT_ERROR_CHECKING_FOR_STATS_ON_ROWS
			//ocu_load_err_msg_str(CER_EXTRACTBYROWSERR_UNEVEN_COLUMNS, &strErr);
			nErr = 1; /// just to skip ocu_load_err_msg_str below
			///------ End BETTER_INPUT_ERROR_CHECKING_FOR_STATS_ON_ROWS
			break;
		///Jasmine 12/08/2016 ORG-10099-S1 STATS_ON_ROWS_SUPPORT_GROUPING
		case EXTRACTBYROWSERR_INVALID_FACTORS:
			ocu_load_err_msg_str(CER_TO_FEW_FACTOR, &strErr);
			break;
		///End STATS_ON_ROWS_SUPPORT_GROUPING
		default:	
		}
		
		if(strErr.IsEmpty() && nErr <= 0)
			ocu_load_err_msg_str(CER_NO_DATA, &strErr);
		
		if(!strErr.IsEmpty())
		{
			okoc_out_msg(strErr);
			return false;
		}
		
		return true;
	}
	
	void setDescStatResults(DescStatResults& stDescStats, double dMean, double dSd, double dSem, 
						double dSum, int N, double dLCL,double  dUCL)
	{
		stDescStats.N 		= N;
		stDescStats.Mean 	= dMean;
		stDescStats.SD 		= dSd;
		stDescStats.SEM 	= dSem;
		stDescStats.LCL 	= dLCL;
		stDescStats.UCL 	= dUCL;
		stDescStats.Sum 	= dSum;
	}
	
	void setQuantileResults(QuantileResults& stQuantiles, double dMin, double dMax, double dQ1, 
						double dMedian, double dQ3)
	{
		stQuantiles.Min		= dMin;
		stQuantiles.Q1		= dQ1;
		stQuantiles.Median	= dMedian;
		stQuantiles.Q3		= dQ3;
		stQuantiles.Max		= dMax;	
	}
	 
	///Arvin 08/31/07 QA70-7651-P17 WRONG_COLUMN_DESIGNATION_TYPE
	//void addDestStatsOnRowsOneResult(TreeNode& trTable, LPCSTR lpcszTagName, int& nID, 
	//		LPCSTR lpcszLabel, int nDataID, vector& vStatsResult, int nInsertCol, vector& vInsertStatsResult)
	///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
	//void addDestStatsOnRowsOneResult(TreeNode& trTable, LPCSTR lpcszTagName, int& nID, 
	//		LPCSTR lpcszLabel, int nDataID, vector& vStatsResult, int nInsertCol, vector& vInsertStatsResult, int nDesignation = OKDATAOBJ_DESIGNATION_Y)
	void checkAddDestStatsOnRowsOneResult(TreeNode& trTable, LPCSTR lpcszTagName, int& nID, 
			///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
			string strInputUnit,
			///End ADD_UNITS_TO_STATISTICS_ON_ROWS
			LPCSTR lpcszLabel, vectorbase* pStatsResult, int nInsertCol, vector& vInsertStatsResult, 
			int& nDataID = NULL, int nDesignation = OKDATAOBJ_DESIGNATION_Y,
			bool bPecentile = false, double* pPercentsAttrib = NULL)
	///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
	///END WRONG_COLUMN_DESIGNATION_TYPE
	{
		///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		if(!pStatsResult)
			return;
		///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		
		TreeNode trRow 			= tree_check_get_node(trTable, lpcszTagName, nID++, STR_LABEL_ATTRIB, lpcszLabel);
		///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		//trRow.DataID			=	nDataID;
		//vInsertStatsResult.SetSubVector( vStatsResult, nInsertCol );
		if(nDataID)
			trRow.DataID		= nDataID;
		vInsertStatsResult.SetSubVector( *pStatsResult, nInsertCol );
		///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		trRow.dVals				= vInsertStatsResult;
		///Arvin 08/31/07 QA70-7651-P17 WRONG_COLUMN_DESIGNATION_TYPE
		trRow.SetAttribute(STR_COL_DESIGNATION_ATTRIB, nDesignation);
		///END WRONG_COLUMN_DESIGNATION_TYPE
		///Shadow 01/16/2017 ORG-16287-S1 ADD_UNITS_TO_STATISTICS_ON_ROWS
		if (strInputUnit != "")
			trRow.SetAttribute(STR_UNIT_ATTRIB, strInputUnit);
		///End ADD_UNITS_TO_STATISTICS_ON_ROWS
		///Cheney 2007-11-14 STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
		if(bPecentile && pPercentsAttrib)
			trRow.SetAttribute(DOUBLE_PERCENTILE_PERCENT_ATTRIBUTE, *pPercentsAttrib);
		///end STATS_ON_ROW_SHOULD_SUPPORT_MORE_OPTION_AS_MAX_SAID
	}
	///end SPEED_UP_STATISTIC_ON_ROW
	
	/// Iris 3/25/2011 ORG-2528-P1 FIX_BOXCHART_PLOT_IN_ONE_GRAPH_ISSUE_IN_STATS_ON_COLS
#ifdef __FIX_STATS_ON_COLS_BOXCHART_PLOT_IN_ONE_GRAPH_ISSUE__
	//virtual 
	DWORD GetInputRangeType() 
	{ 
		DWORD dwType = StatsOpBase::GetInputRangeType();
		return dwType | NTYPE_ADD_ROW_RANGE; 
	}
	
	//virtual 
	DWORD GetAddPlotOptions() 
	{ 
		DWORD dwOptions = StatsOpBase::GetAddPlotOptions();
		return dwOptions | GAP_ALLOW_DUPLICATE_COL;
	}
#endif //__FIX_STATS_ON_COLS_BOXCHART_PLOT_IN_ONE_GRAPH_ISSUE__
	///End FIX_BOXCHART_PLOT_IN_ONE_GRAPH_ISSUE_IN_STATS_ON_COLS

	///Kyle 08/07/2015 ORG-12921-P1 STATS_ON_COL_SKIP_EMPTY_OUTPUT_PLOTS
	bool 	CheckExcludeEmptyPlot(TreeNode& trOp, int nGraphIndex, DataRange& drPlot)
	{
		if( DescStatsExcludeEmptyDataset(trOp) )
		{
			switch( ReportGetPlotTypeFromGraphIndex(nGraphIndex) )
			{
			case IDM_PLOT_BOX:
			case IDM_PLOT_HISTOGRAM_TYPE:
				{
					vector vData;
					drPlot.GetData(&vData, 0);

					if( 0 == vData.GetSize() || 0 == vData.Find(MATREPL_TEST_LESSTHAN | MATREPL_TEST_GREATER, NANUM, NULL, 0, -1, 0, VECTORBASEFIND_IF_ONE_MATCH_THEN_RETURN) )
						return true;
				}
			}
		}

		return StatsOpBase::CheckExcludeEmptyPlot(trOp, nGraphIndex, drPlot);
	}
	///End STATS_ON_COL_SKIP_EMPTY_OUTPUT_PLOTS

	///------ Folger 07/02/2012 ORG-5592-S1 SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET
	virtual DWORD GetConvertEscapeStrForFlatSheetCtrnl() { return IsOutputDataIdentifierFlatSheet() ? (CONVERT_ESCAPED_STR_FOR_FLAT_SHEET__DATA | CONVERT_ESCAPED_STR_FOR_FLAT_SHEET__LABEL) : 0; }
	///------ End SHOW_DATA_IDENTIFIER_FOR_FLAT_SHEET

	///------ Folger 08/24/2012 ORG-6311-P1 UPDATE_DATASET_INDENTIFIER_FOR_FLAT_SHEET_FROM_CONTEXT_MENU
	/// Hong 07/20/2016 ORG-14278 FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
	//virtual void UpdateDataIdentifiersFlatSheet(LPCSTR lpcszDataOld, LPCSTR lpcszDataNew)
	///------ Tony 01/09/2020 ORG-21274-S1 DATASET_IDENTIFY_USE_NEW_CONTROL
	//virtual void UpdateDataIdentifiersFlatSheet(int nTypeOld, LPCSTR lpcszDataOld, int nTypeNew, LPCSTR lpcszDataNew)
	///// end FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
	//{
		///// Hong 07/22/2016 ORG-14278 FIX_DATA_IDENTIFIER_FAIL_UPDATE_BY_REPORT_SHEET_CONTEXT_MENU
		//TreeNode	trOp;
		//GetTree(trOp);
		//BOOL		bCombineMultiAsSingle = IsCombinedMultiAsSingle(trOp);
		///// end FIX_DATA_IDENTIFIER_FAIL_UPDATE_BY_REPORT_SHEET_CONTEXT_MENU
		//int nNumOutputs = GetOutputCount();
		//for ( int ii=0; ii<nNumOutputs; ++ii )
		//{
			//DataRange rng;
			//GetOutput(rng, ii);
//
			//Worksheet wks;
			//if ( !IsRangeHierarchicalSheet(rng, wks) && wks )
			//{
				//Column col(wks, 0);
				//if ( col )
				//{
					//vector<string> vs;
					//col.GetStringArray(vs);
//
					//bool bReplaced = false;
					//for ( int jj=0; jj<vs.GetSize(); ++jj )
					//{
						//bReplaced = vs[jj].Replace(lpcszDataOld, lpcszDataNew) > 0;
						///// Hong 07/20/2016 ORG-14278 FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
						///// Hong 07/22/2016 ORG-14278 FIX_DATA_IDENTIFIER_FAIL_UPDATE_BY_REPORT_SHEET_CONTEXT_MENU
						//if (bCombineMultiAsSingle)
							//continue;
						///// end FIX_DATA_IDENTIFIER_FAIL_UPDATE_BY_REPORT_SHEET_CONTEXT_MENU
						//string		strDataOld = lpcszDataOld, strDataNew = lpcszDataNew;
						//bool	bUseCellLink = check_update_data_identifier_label(strDataNew, nTypeNew, jj);
						//if (bReplaced && bUseCellLink)
							//vs[jj] = strDataNew;
						//else if (!bReplaced)
						//{
							//if (!bUseCellLink)
							//{
								//string		strDataIndex;
								//strDataIndex.Format("=%d", jj + 1);
								//strDataNew += strDataIndex;
							//}
							///// Hong 07/22/2016 ORG-14278 FIX_DATA_IDENTIFIER_FAIL_UPDATE_BY_REPORT_SHEET_CONTEXT_MENU
							////if (check_update_data_identifier_label(strDataOld, nTypeOld, jj))
							////	bReplaced = vs[jj].Replace(strDataOld, strDataNew) > 0;
							//if (vs[jj].Find(STR_CELL_REF_PREFIX, 0, FALSE) >= 0)
							//{
								//vs[jj] = strDataNew;
								//bReplaced = true;
							//}
							///// end FIX_DATA_IDENTIFIER_FAIL_UPDATE_BY_REPORT_SHEET_CONTEXT_MENU
						//}
						///// end FIX_OPERATION_NOT_DIRTY_WHEN_INPUT_IS_DESCSTATS_DATASET_INDENTIFIER
					//}
//
					//if ( bReplaced )
					//{
						//OperationAccessToken token(this);
						//col.PutStringArray(vs);
					//}
				//}
				//break;
			//}			
		//}
	//}
	
	virtual void UpdateDataIdentifiersFlatSheet(TreeNode& trOp, const vector<string>& vsDataLabelEscapedStringKey, const vector<int>& vnDataType, const vector<string>& vsDataType)
	{
		TreeNode trFlatTable = trOp.ResidualCurves.FlatOut;
		if(!trFlatTable)
			return;
		const string strTableTagName = "C1";
		TreeNode trFlatRow = trFlatTable.GetNode(strTableTagName);
		if(!trFlatRow)
			return;

		// clear all flat report data col
		///------ Folger 02/04/2020 ORG-21417-P1 STATS_ON_COLUMNS_PROPER_REPORT_DATA_COLUMN_IDS
		//for(int nId = IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL; nId <= IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL_END; nId++)
		//{
			//TreeNode trOld = tree_get_node_by_dataid(trFlatRow, nId);
		for (int ii=0; ii<TOTAL_NUMBER_OF_REPORT_DATA_COL_ID; ++ii)
		{
			TreeNode trOld = tree_get_node_by_dataid(trFlatRow, _GetReportDataColID(ii));
		///------ End STATS_ON_COLUMNS_PROPER_REPORT_DATA_COLUMN_IDS
			if(!trOld)
				break;

			trOld.Remove();
		}

		DataRange		dr;
		GetInput(dr);

		TreeNode		trAdditionalData = tree_check_get_node(trOp,TREE_INPUTRANGE_ADDITIONAL_DATA_NODE_NAME); 
		int nNumData = GetNumData(trOp, dr, trAdditionalData);
		for(int nIndex = 0; nIndex < nNumData; nIndex++)
		{
			vector<string> vsDataLabel;
			GetOneDataLabel(trOp, nIndex, nIndex, vsDataLabel);
			UpdateDataIdentifiersFlatSheet(trOp, vsDataLabel, nIndex);
		}
		
		DataRange drFlatOut;	
		GetOutput(drFlatOut, GetOutputSlot(0, true, OUTPUT_FLAT_RESULT_SHEET));

		Worksheet wks;
		if( drFlatOut )
			drFlatOut.GetParent(wks);
		
		if( wks )
		{
			TreeNode trResidualCurves = trOp.ResidualCurves;
			trResidualCurves.SetAttribute(TREE_REPLACE, 1);

			DWORD dwOptions = SETGRTR_NO_SET_COLUMN_NAME_IN_FLAT_FOR_VECTOR | SETGRTR_ALWAYS_UPDATE_COLUMN_LABELS;
			wks.SetReportTree(trResidualCurves, 0, dwOptions);
			autosize_rowcol(wks);
		}
	}
	
	void UpdateDataIdentifiersFlatSheet(TreeNode& trOp, const vector<string>& vsDataLabel, int nIndex)
	{
		TreeNode trFlatTable = trOp.ResidualCurves.FlatOut;
		if(!trFlatTable)
			return;
		const string strTableTagName = "C1";
		TreeNode trFlatRow = trFlatTable.GetNode(strTableTagName);
		if(!trFlatRow)
			return;
		
		BOOL	bOutputDataIdentifierFlatSheet = IsOutputDataIdentifierFlatSheet(&trOp);
		BOOL	bCombineMultiAsSingle = IsCombinedMultiAsSingle(trOp);
		string strWeightData;
		int		indexLT = nIndex + 1;
		BOOL bAutoUpdateNone = GetAUMode() == AU_NONE;
		if( IsDatasetHasWeight(trOp.GUI.InputData, nIndex) )
		{
			string strWeightData;
			report_get_escaped_data_string(&strWeightData, indexLT, FALSE, 'I', 'W');
			if ( bAutoUpdateNone )
				ConvertEscapedString(strWeightData);
		}
		
		string strBookSheet;
		report_get_escaped_data_string(&strBookSheet, indexLT, FALSE, 'D');
		if ( bAutoUpdateNone )
			ConvertEscapedString(strBookSheet);
		
		for(int nn = vsDataLabel.GetSize() - 1; nn >= 0; nn--)
		{
			///------ Folger 02/04/2020 ORG-21417-P1 STATS_ON_COLUMNS_PROPER_REPORT_DATA_COLUMN_IDS
			//int nDataId = IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL + nn;
			//if(nDataId > IDST_STATS_ON_COLS_FLAT_REPORT_DATA_COL_END)
			int nDataId = _GetReportDataColID(nn);
			if (nDataId == 0)
			///------ End STATS_ON_COLUMNS_PROPER_REPORT_DATA_COLUMN_IDS
			{
				ASSERT(FALSE); // MAX ID reached
				continue;
			}
			
			string strDataLabel = vsDataLabel[nn];
			string strDataNodeTagName = "Data";
			if(nn > 0)
				strDataNodeTagName += nn;
			TreeNode trDataLabel = trFlatRow.GetNode(strDataNodeTagName);
			if ( !bOutputDataIdentifierFlatSheet )
			{
				if ( trDataLabel )
					trDataLabel.Remove();
				return;
			}

			if( !trDataLabel )
			{
				if ( trFlatRow.FirstNode )
					trDataLabel = trFlatRow.InsertNode(trFlatRow.FirstNode, strDataNodeTagName);
				else
					trDataLabel = trFlatRow.AddNode(strDataNodeTagName);
			}
			trDataLabel.DataID = nDataId;
			trDataLabel.SetAttribute(STR_LABEL_ATTRIB, GetLocalized(strDataNodeTagName));
			trDataLabel.SetAttribute(STR_COL_DESIGNATION_ATTRIB, OKDATAOBJ_DESIGNATION_X);
			
			BOOL	bDataFromSameSheet = setDataIndentifierInFlatSheet(trDataLabel, nIndex, strDataLabel, bAutoUpdateNone, bCombineMultiAsSingle, trOp, nn);
			if (bDataFromSameSheet)
				trDataLabel.SetAttribute(STR_USER_PARAM_ATTRIB_PREFIX, _L("Source") + "|" + strBookSheet);				
			else
				trDataLabel.RemoveAttribute(STR_USER_PARAM_ATTRIB_PREFIX);

			if( !strWeightData.IsEmpty() )
			{
				string strAttribName = STR_USER_PARAM_ATTRIB_PREFIX + 2;
				trDataLabel.SetAttribute(strAttribName, _L("Weight") + "|" + strWeightData);				
			}
		}
	}
	///------ End DATASET_IDENTIFY_USE_NEW_CONTROL
	///------ End UPDATE_DATASET_INDENTIFIER_FOR_FLAT_SHEET_FROM_CONTEXT_MENU

	///------ Folger 09/17/2012 ORG-6829-P1 FAILED_TO_SHOW_SUB_DATA_INDEX_IN_STATS_ON_COLUMN_REPORT_SHEET
	virtual int GetEscapedMainDataStringAdditional(TreeNode& trOp, int indexLT)
	{
		if(trOp.MultiRanges)
		{
			int nIndex = indexLT - 1;
			vector<int> vnMRindeces;
			vnMRindeces = trOp.MultiRanges.nVals;
			if(vnMRindeces[nIndex] > 0)
				return MAKELONG(ESC_LABEL_ADD_INDEX, vnMRindeces[nIndex]);
		}

		return ESC_LABEL_ADD_NONE;
	}
	///------ End FAILED_TO_SHOW_SUB_DATA_INDEX_IN_STATS_ON_COLUMN_REPORT_SHEET

	///------ Folger 05/02/2013 ORG-8563-P1 DATASET_ID_LABEL_ROW_FAILED_TO_SHOW_IN_STATS_ON_COLUMN
	/////------ Folger 12/13/2012 ORG-7618-P3 PROPER_SHOW_DATASET_IDENTIFIER_IN_FLAT_SHEET_IF_MORE_THAN_ONE_USER_PARAM
	//virtual bool UpdateDatasetIdentifierFlatSheetLabel(TreeNode& trReport) { return false; }
	/////------ End PROPER_SHOW_DATASET_IDENTIFIER_IN_FLAT_SHEET_IF_MORE_THAN_ONE_USER_PARAM
	///------ End DATASET_ID_LABEL_ROW_FAILED_TO_SHOW_IN_STATS_ON_COLUMN
	
	///------ Folger 08/20/2014 ORG-4941-P1 DESCSTATS_SHOULD_NOT_OUTPUT_FLAT_REPORT_FOR_OPJ_BEFORE_86
	virtual void GUIOnUpdateTreeBeforeRunning(const MultipleVersion& mvOld, TreeNode &trGUINew, TreeNode &trGUIOriginal, TreeNode& trOperation)
	{
		StatsOpBase::GUIOnUpdateTreeBeforeRunning(mvOld, trGUINew, trGUIOriginal, trOperation);
		if ( is_integer_part_less_then(mvOld.GetVersion(STR_OP_NAME_DESCSTATS_OP), m_mvCur.GetVersion(STR_OP_NAME_DESCSTATS_OP)) )
		{
			if (!trGUIOriginal.Output.FlatOut)
			{
				trGUINew.Output.FlatOut.Book.strVal = STR_NONE;
			}
		}
	}
	///------ End DESCSTATS_SHOULD_NOT_OUTPUT_FLAT_REPORT_FOR_OPJ_BEFORE_86
	
	///------ Folger 08/12/2015 ORG-13447-P1 STATS_ON_COL_SHOULD_NOT_SKIP_EMPTY_INPUT_WHEN_RECALCULATE
	virtual bool IsSkipCalcWhenInputEmpty(int nExecMode) { return FALSE; }
	///------ End STATS_ON_COL_SHOULD_NOT_SKIP_EMPTY_INPUT_WHEN_RECALCULATE
	
	///------ Folger 09/03/2020 ORG-22216-P3 OPERATION_TOOLS_SUPPORT_SORT_BY_FACTORS
	virtual bool NeedSortByFactor(DWORD& dwCntrl)
	{
		dwCntrl = RANGE_SORT_BY_FACTOR__SPECIAL_SORT;
		return true;
	}
	///------ End OPERATION_TOOLS_SUPPORT_SORT_BY_FACTORS
};

void mkdsdata(int npts = 100, bool b2Factor=true)
{
	Worksheet wks = Project.ActiveLayer();
	wks.SetSize(npts, b2Factor? 3:2);
	
	Dataset aa(wks, 0);
	aa.SetSize(npts);
	string str;
	double r1;
	for(int ii = 0; ii < npts; ii++)
	{
		r1 = rnd();
		aa[ii] = 100 * rnd() + ii * 0.1;
		str = r1 > 0.5? "Male" : "Female";
		if(r1 > 0.5)
			aa[ii] += 15*rnd();
		wks.SetCell(ii, 1, str);
		if(b2Factor)
		{
			r1 = rnd();
			str = r1 > 0.5? "40-69" : "20-39";
			wks.SetCell(ii, 2, str);
			if(r1 < 0.5)
				aa[ii] += 10*rnd();				
		}
	}
	Column ca(wks, 0);
	ca.SetLongName("Driver Safety Index");
	Column cb(wks, 1);
	cb.SetLongName("Gender");
	if(b2Factor)
	{
		Column cc(wks, 2);
		cc.SetLongName("Age Group");
	}
}


