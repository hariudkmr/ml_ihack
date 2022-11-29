###########################################
# Project:      CMSIS DSP Library
# Title:        GenMFCCDataForCPP.py
# Description:  Generation of MFCC arrays for the MFCC function
#
# $Date:        07 September 2021
# $Revision:    V1.10.0
#
# Target Processor: Cortex-M and Cortex-A cores
# -------------------------------------------------------------------- */
#
# Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the License); you may
# not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an AS IS BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
############################################

#########################
#
# This script is generating arrays required by the MFCC implementation:
# DCT coefficients and Mel filters
# Those arrays must be used with the arm_mfcc_init functions
# The configuration is done through a yaml file describing the values for the
# MFCC and the type
#
import argparse
import yaml
import mfccdata
import os
import os.path

# python GenMFCCDataForCPP.py -n "mfcc_data" -d "./MFCC_Data" -i "./MFCC_Data" mfccconfig_2.yaml

parser = argparse.ArgumentParser(description="Generate MFCC Data for CPP")


parser.add_argument(
    "-n", 
    nargs="?", 
    type=str, 
    default="mfccdata", 
    help="mfcc file name"
)
parser.add_argument(
    "-d",
    nargs="?",
    type=str,
    default="Testing/Source/Tests",
    help="mfcc c file directory",
)
parser.add_argument(
    "-i",
    nargs="?",
    type=str,
    default="Testing/Include/Tests",
    help="mfcc h file directory",
)
parser.add_argument(
    "-t",
    nargs="?",
    type=str,
    default="file_templates",
    help="Directory that contains the template files",
)
parser.add_argument(
    "-cfile",
    nargs="?",
    type=str,
    default="mfcc_data_template.c",
    help=".c template filename",
)
parser.add_argument(
    "-hfile",
    nargs="?",
    type=str,
    default="mfcc_data_template.h",
    help=".h template filename",
)
parser.add_argument("others", help="yaml configuration file", nargs=argparse.REMAINDER)

args = parser.parse_args()


if args.n and args.d and args.t and args.cfile and args.hfile and args.others:
    cpath = os.path.join(args.d, args.n + ".c")
    cpath_folder = args.d
    hpath = os.path.join(args.i, args.n + ".h")
    hpath_folder = args.i

    with open(args.others[0], "r") as f:
        configs = yaml.safe_load(f)

        mfccdata.setTemplateConfig(args.t, args.cfile, args.hfile)
        mfccdata.checkF16(configs)
        mfccdata.prepareDctconfig(configs["dct"])
        mfccdata.prepareMelconfig(configs["melfilter"])
        mfccdata.prepareWindowConfig(configs["window"])

        if not os.path.exists(hpath_folder):
            os.makedirs(hpath_folder)

        with open(hpath, "w") as h:
            mfccdata.genMfccHeader(h, configs, args.n)

        if not os.path.exists(cpath_folder):
            os.makedirs(cpath_folder)

        with open(cpath, "w") as c:
            mfccdata.genMfccInit(c, configs, args.n)
else:
    print("Invalid arguments")
