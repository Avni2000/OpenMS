// Copyright (c) 2002-present, OpenMS Inc. -- EKU Tuebingen, ETH Zurich, and FU Berlin
// SPDX-License-Identifier: BSD-3-Clause
//
// --------------------------------------------------------------------------
// $Maintainer: Your Name $
// $Authors: Your Name $
// --------------------------------------------------------------------------

#include <OpenMS/FORMAT/FeatureCSVFile.h>

#include <OpenMS/CONCEPT/LogStream.h>
#include <OpenMS/FORMAT/FileHandler.h>
#include <OpenMS/FORMAT/FileTypes.h>
#include <OpenMS/SYSTEM/File.h>

#include <fstream>

using namespace std;

namespace OpenMS
{

  FeatureCSVFile::FeatureCSVFile() : 
    separator_(',')
  {
  }

  FeatureCSVFile::~FeatureCSVFile() = default;

  void FeatureCSVFile::store(const String& filename, const FeatureMap& feature_map)
  {
    // Check file extension
    if (!FileHandler::hasValidExtension(filename, FileTypes::FEATURECSV))
    {
      throw Exception::UnableToCreateFile(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION, 
                                         filename, "invalid file extension, expected '.featurecsv'");
    }

    // Open output file
    ofstream os(filename.c_str());
    if (!os)
    {
      throw Exception::UnableToCreateFile(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION, filename);
    }

    // Write header
    os << generateHeader_() << endl;

    // Write feature data
    for (const auto& feature : feature_map)
    {
      os << featureToCSVRow_(feature) << endl;
    }

    os.close();

    OPENMS_LOG_INFO << "Stored " << feature_map.size() << " features in CSV format to '" 
                    << filename << "'." << endl;
  }

  void FeatureCSVFile::load(const String& /* filename */, FeatureMap& /* feature_map */)
  {
    // TODO: Implement CSV loading functionality
    throw Exception::NotImplemented(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION);
  }

  void FeatureCSVFile::setSeparator(char separator)
  {
    separator_ = separator;
  }

  char FeatureCSVFile::getSeparator() const
  {
    return separator_;
  }

  String FeatureCSVFile::generateHeader_() const
  {
    String header = "RT";
    header += separator_;
    header += "MZ";
    header += separator_;
    header += "Intensity";
    header += separator_;
    header += "Charge";
    header += separator_;
    header += "FWHM";
    header += separator_;
    header += "Quality";
    header += separator_;
    header += "ID";
    header += separator_;
    header += "NumSubordinates";
    
    return header;
  }

  String FeatureCSVFile::featureToCSVRow_(const Feature& feature) const
  {
    String row = String(feature.getRT());
    row += separator_;
    row += String(feature.getMZ());
    row += separator_;
    row += String(feature.getIntensity());
    row += separator_;
    row += String(feature.getCharge());
    row += separator_;
    row += String(feature.getWidth());
    row += separator_;
    row += String(feature.getOverallQuality());
    row += separator_;
    row += String(feature.getUniqueId());
    row += separator_;
    row += String(feature.getSubordinates().size());

    return row;
  }

} // namespace OpenMS
