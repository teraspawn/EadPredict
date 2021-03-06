/*

Copyright (c) 2005-2017, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of Chaste.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of the University of Oxford nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef TESTDATAREADERS_HPP_
#define TESTDATAREADERS_HPP_

#include <cxxtest/TestSuite.h>

#include "DrugDataReader.hpp"
#include "AbstractDataStructure.hpp"

class TestDataReaders : public CxxTest::TestSuite
{
public:
    void TestDrugDataLoading(void) throw(Exception)
    {
        FileFinder file("projects/EadPredict/test/curated_dataset.dat", RelativeTo::ChasteSourceRoot);

        // Test the drug data loads correctly...
        DrugDataReader drug_data(file);
        TS_ASSERT_EQUALS(drug_data.GetNumDrugs(), 42);

        unsigned ajmaline_idx = 0;
	TS_ASSERT_EQUALS(drug_data.GetDrugName(ajmaline_idx),"ajmaline");
	TS_ASSERT_DELTA(drug_data.GetClinicalDoseRange(ajmaline_idx,0),65,1e-4);

	unsigned quinidine = 32;
        unsigned cisapride =7 ;
        unsigned tedisamil = 36;
        unsigned propranolol = 30;
        unsigned verapamil = 40;

        TS_ASSERT_EQUALS(drug_data.GetDrugName(quinidine), "quinidine");
        TS_ASSERT_EQUALS(drug_data.GetDrugName(cisapride), "cisapride");
        TS_ASSERT_EQUALS(drug_data.GetDrugName(tedisamil), "tedisamil");
        TS_ASSERT_EQUALS(drug_data.GetDrugName(propranolol), "propranolol");
        TS_ASSERT_EQUALS(drug_data.GetDrugName(verapamil), "verapamil");
        TS_ASSERT_DELTA(drug_data.GetIC50Value(quinidine,0), 16600, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetIC50Value(cisapride,2), 6.5, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetIC50Value(propranolol,1), 18000, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetIC50Value(propranolol,2), 2828, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetClinicalDoseRange(quinidine,0), 924, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetClinicalDoseRange(quinidine,1), 3237, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetClinicalDoseRange(cisapride,0), 2.6, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetClinicalDoseRange(cisapride,1), 4.9, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetClinicalDoseRange(verapamil,0), 25, 1e-4);
        TS_ASSERT_DELTA(drug_data.GetClinicalDoseRange(verapamil,1), 81, 1e-4);


        // We want a "no effect drug" to return DBL_MAX, which the CalculateConductanceFactor() method handles nicely (see below).
        unsigned pentamidine = 25 ;
        TS_ASSERT_EQUALS(drug_data.GetDrugName(pentamidine),"pentamidine");
        TS_ASSERT_DELTA(drug_data.GetIC50Value(pentamidine,1), std::numeric_limits<double>::max(), 1e-9);

        // Check how it deals with a "NA" (No effect) entry - should return DBL_MAX for the IC50.
        // (i.e. a positive value which won't effect conductance so that analysis will run)
        TS_ASSERT_EQUALS(drug_data.GetDrugName(tedisamil), "tedisamil");
        TS_ASSERT_DELTA(drug_data.GetIC50Value(tedisamil,0), 20000, 1e-9);
        TS_ASSERT_DELTA(drug_data.GetIC50Value(tedisamil,1), std::numeric_limits<double>::max(), 1e-9);
    }

};

#endif // TESTDATAREADERS_HPP_
