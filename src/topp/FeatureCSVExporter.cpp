// Copyright (c) 2002-present, OpenMS Inc. -- EKU Tuebingen, ETH Zurich, and FU Berlin
// SPDX-License-Identifier: BSD-3-Clause
//
// --------------------------------------------------------------------------
// $Maintainer: Your Name $
// $Authors: Your Name $
// --------------------------------------------------------------------------

#include <OpenMS/APPLICATIONS/TOPPBase.h>
#include <OpenMS/FORMAT/FileHandler.h>
#include <OpenMS/FORMAT/FeatureCSVFile.h>
#include <OpenMS/FORMAT/FileTypes.h>
#include <OpenMS/KERNEL/FeatureMap.h>

using namespace OpenMS;
using namespace std;

//-------------------------------------------------------------
//Doxygen docu
//-------------------------------------------------------------

/**
@page TOPP_FeatureCSVExporter FeatureCSVExporter

@brief This application converts featureXML files to CSV format.

<CENTER>
  <table>
   <tr>
    <th ALIGN = "center"> potential predecessor tools </td>
       <td VALIGN="middle" ROWSPAN=2> &rarr; FeatureCSVExporter &rarr;</td>
   <th ALIGN = "center"> potential successor tools </td>
  </tr>
  <tr>
    <td VALIGN="middle" ALIGN = "center" ROWSPAN=1> FeatureFinderCentroided, FeatureFinderMetabo, etc. </td>
    <td VALIGN="middle" ALIGN = "center" ROWSPAN=1> External tools (Excel, R, Python)</td>
  </tr>
 </table>
</CENTER>

This tool exports basic feature information (RT, m/z, intensity, charge, etc.) to a simple CSV format for external analysis.

<B>The command line parameters of this tool are:</B>
@verbinclude TOPP_FeatureCSVExporter.cli
<B>INI file documentation of this tool:</B>
@htmlinclude TOPP_FeatureCSVExporter.html
 */

// We do not want this class to show up in the docu:
/// @cond TOPPCLASSES

namespace OpenMS
{
  class TOPPFeatureCSVExporter :
    public TOPPBase
  {
public:
    TOPPFeatureCSVExporter() :
      TOPPBase("FeatureCSVExporter", "Exports featureXML files to CSV format.", false)
    {
    }

protected:

    void registerOptionsAndFlags_() override
    {
      registerInputFile_("in", "<file>", "", "Input featureXML file", true);
      setValidFormats_("in", ListUtils::create<String>("featureXML"));
      registerOutputFile_("out", "<file>", "", "Output CSV file", true);
      setValidFormats_("out", ListUtils::create<String>("csv"));
    }

    ExitCodes main_(int, const char**) override
    {
      // TODO: Implement main functionality
      
      String input_file = getStringOption_("in");
      String output_file = getStringOption_("out");
      
      char separator = ',';
      
      // Load FeatureMap
      FeatureMap feature_map;
      FileHandler().loadFeatures(input_file, feature_map, {FileTypes::FEATUREXML});
      
      writeLogInfo_(String("Loaded ") + feature_map.size() + " features from '" + input_file + "'");
      
      // Export to CSV
      FeatureCSVFile csv_file;
      csv_file.setSeparator(separator);
      csv_file.store(output_file, feature_map);
      
      writeLogInfo_(String("Exported features to CSV file '") + output_file + "'");
      
      return EXECUTION_OK;
    }

  };
}

/// @endcond

int main(int argc, const char** argv)
{
  TOPPFeatureCSVExporter tool;
  return tool.main(argc, argv);
}
