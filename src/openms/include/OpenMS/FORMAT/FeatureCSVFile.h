// Copyright (c) 2002-present, OpenMS Inc. -- EKU Tuebingen, ETH Zurich, and FU Berlin
// SPDX-License-Identifier: BSD-3-Clause
//
// --------------------------------------------------------------------------
// $Maintainer: Your Name $
// $Authors: Your Name $
// --------------------------------------------------------------------------

#pragma once

#include <OpenMS/KERNEL/FeatureMap.h>
#include <OpenMS/FORMAT/CsvFile.h>
#include <OpenMS/DATASTRUCTURES/String.h>

namespace OpenMS
{
  /**
    @brief File adapter for feature files in CSV format.

    This class exports FeatureMap data to a simple CSV format containing 
    basic feature information such as RT, m/z, intensity, and charge.

    @ingroup FileIO
  */
  class OPENMS_DLLAPI FeatureCSVFile
  {
  public:

    /// Default constructor
    FeatureCSVFile();

    /// Destructor
    ~FeatureCSVFile();

    /**
      @brief Stores a FeatureMap as CSV file

      @param filename The output file name
      @param feature_map The feature map to store

      @exception Exception::UnableToCreateFile is thrown if the file could not be created
    */
    void store(const String& filename, const FeatureMap& feature_map);

    /**
      @brief Loads a CSV file into a FeatureMap (stub - not implemented yet)

      @param filename The input file name  
      @param feature_map The feature map to load into

      @exception Exception::FileNotFound is thrown if the file could not be found
      @exception Exception::ParseError is thrown if parsing fails
    */
    void load(const String& filename, FeatureMap& feature_map);

    /**
      @brief Set the separator character for CSV output

      @param separator The separator character (default: ',')
    */
    void setSeparator(char separator);

    /**
      @brief Get the current separator character

      @return The separator character
    */
    char getSeparator() const;

  private:

    /// CSV separator character
    char separator_;

    /// Generate CSV header line
    String generateHeader_() const;

    /// Convert a feature to CSV row
    String featureToCSVRow_(const Feature& feature) const;

  };

} // namespace OpenMS
