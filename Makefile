################################################################################
# \file Makefile
# \version 1.0
#
# \brief
# Top-level application make file.
#
################################################################################
# \copyright
# Copyright 2018-2022, Cypress Semiconductor Corporation (an Infineon company)
# SPDX-License-Identifier: Apache-2.0
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################


################################################################################
# Basic Configuration
################################################################################

# Target board/hardware (BSP).
# To change the target, it is recommended to use the Library manager
# ('make modlibs' from command line), which will also update Eclipse IDE launch
# configurations. If TARGET is manually edited, ensure TARGET_<BSP>.mtb with a
# valid URL exists in the application, run 'make getlibs' to fetch BSP contents
# and update or regenerate launch configurations for your IDE.
TARGET=CY8CPROTO-062-4343W

# Name of application (used to derive name of final linked file).
#
# If APPNAME is edited, ensure to update or regenerate launch
# configurations for your IDE.
APPNAME=marvin_ml_solver

# Name of toolchain to use. Options include:
#
# GCC_ARM -- GCC provided with ModusToolbox IDE
# ARM     -- ARM Compiler (must be installed separately)
# IAR     -- IAR Compiler (must be installed separately)
#
# See also: CY_COMPILER_PATH below
TOOLCHAIN=GCC_ARM

# Default build configuration. Options include:
#
# Debug -- build with minimal optimizations, focus on debugging.
# Release -- build with full optimizations
# Custom -- build with custom configuration, set the optimization flag in CFLAGS
#
# If CONFIG is manually edited, ensure to update or regenerate launch configurations
# for your IDE.
CONFIG=Debug

# If set to "true" or "1", display full command-lines when building.
VERBOSE=

# Model Name to be loaded to the firmware
NN_MODEL_NAME=VOICE_CONTROL_PSOC6


################################################################################
# Advanced Configuration
################################################################################

# Enable optional code that is ordinarily disabled by default.
#
# Available components depend on the specific targeted hardware and firmware
# in use. In general, if you have
#
#    COMPONENTS=foo bar
#
# ... then code in directories named COMPONENT_foo and COMPONENT_bar will be
# added to the build
#
COMPONENTS=

# Like COMPONENTS, but disable optional code that was enabled by default.
DISABLE_COMPONENTS=

# By default the build system automatically looks in the Makefile's directory
# tree for source code and builds it. The SOURCES variable can be used to
# manually add source code to the build process from a location not searched
# by default, or otherwise not found by the build system.
SOURCES=


# Exclude the CMSIS root directory from build but add only the DSP Source and 
# Include directories for auto-discovery search
CY_IGNORE=$(SEARCH_CMSIS_5)
CMSIS_DSP_DIR=$(SEARCH_CMSIS_5)/CMSIS/DSP

# Add the required source files from the CMSIS DSP library
SOURCES+=$(CMSIS_DSP_DIR)/Source/BasicMathFunctions/BasicMathFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/BasicMathFunctions/BasicMathFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/BayesFunctions/BayesFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/BayesFunctions/BayesFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/CommonTables/CommonTables.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/CommonTables/CommonTablesF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/ComplexMathFunctions/ComplexMathFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/ComplexMathFunctions/ComplexMathFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/ControllerFunctions/ControllerFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/DistanceFunctions/DistanceFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/DistanceFunctions/DistanceFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/FastMathFunctions/FastMathFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/FastMathFunctions/FastMathFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/FilteringFunctions/FilteringFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/FilteringFunctions/FilteringFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/InterpolationFunctions/InterpolationFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/InterpolationFunctions/InterpolationFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/MatrixFunctions/MatrixFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/MatrixFunctions/MatrixFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/QuaternionMathFunctions/QuaternionMathFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/StatisticsFunctions/StatisticsFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/StatisticsFunctions/StatisticsFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/SupportFunctions/SupportFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/SupportFunctions/SupportFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/SVMFunctions/SVMFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/SVMFunctions/SVMFunctionsF16.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/TransformFunctions/TransformFunctions.c
SOURCES+=$(CMSIS_DSP_DIR)/Source/TransformFunctions/TransformFunctionsF16.c


# Like SOURCES, but for include directories. Value should be paths to
# directories (without a leading -I).
INCLUDES=$(CMSIS_DSP_DIR)/Include
INCLUDES+=$(CMSIS_DSP_DIR)/PrivateInclude source
INCLUDES+=source

# Add additional defines to the build process (without a leading -D).
DEFINES+=CY_RETARGET_IO_CONVERT_LF_TO_CRLF 

############################# ML related defines ##############################

# Neural Network Configuration. Options include
#
# float    -- floating point for the input data and weights
# int8x8   -- 8-bit fixed-point for the input data and weights
# int16x8  -- 16-bit fixed-point for the input data and 8-bit for weights
# int16x16 -- 16-bit fixed-point for the input data and weights
NN_TYPE=float

# Folder name containing the model and regression data
NN_MODEL_FOLDER=./mtb_ml_gen

# Other defines for the MTB ML configurations
DEFINES+=MODEL_NAME=$(NN_MODEL_NAME)
INCLUDES+=$(NN_MODEL_FOLDER)/mtb_ml_regression_data $(NN_MODEL_FOLDER)/mtb_ml_models

# Depending which Neural Network Type, add a specific DEFINE and COMPONENT
ifeq (float, $(NN_TYPE))
DEFINES+=CY_ML_FLOATING_POINT_fltxflt_NN=1
COMPONENTS+=ML_FLOAT32
endif

ifeq (int16x16, $(NN_TYPE))
DEFINES+=CY_ML_FIXED_POINT_16_IN=1 CY_ML_FIXED_POINT_16_NN=1 
COMPONENTS+=ML_INT16x16
endif

ifeq (int16x8, $(NN_TYPE))
DEFINES+=CY_ML_FIXED_POINT_16_IN=1 CY_ML_FIXED_POINT_8_NN=1 
COMPONENTS+=ML_INT16x8
endif

ifeq (int8x8, $(NN_TYPE))
DEFINES+=CY_ML_FIXED_POINT_8_IN=1 CY_ML_FIXED_POINT_8_NN=1
COMPONENTS+=ML_INT8x8
endif

DEFINES+=ARM_MATH_CM4=1
DEFINES+=__FPU_PRESENT=1

# Select softfp or hardfp floating point. Default is softfp.
VFP_SELECT=

# Additional / custom C compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CFLAGS=

# Additional / custom C++ compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CXXFLAGS=

# Additional / custom assembler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
ASFLAGS=

# Additional / custom linker flags.
LDFLAGS=

# Additional / custom libraries to link in to the application.
# LDLIBS=$(wildcard -l$(CMSIS_DSP_DIR)/Lib/GCC/*.a)
LDLIBS=

# Path to the linker script to use (if empty, use the default linker script).
LINKER_SCRIPT=

# Custom pre-build commands to run.
PREBUILD=

# Custom post-build commands to run.
POSTBUILD=


################################################################################
# Paths
################################################################################

# Relative path to the project directory (default is the Makefile's directory).
#
# This controls where automatic source code discovery looks for code.
CY_APP_PATH=

# Relative path to the shared repo location.
#
# All .mtb files have the format, <URI>#<COMMIT>#<LOCATION>. If the <LOCATION> field
# begins with $$ASSET_REPO$$, then the repo is deposited in the path specified by
# the CY_GETLIBS_SHARED_PATH variable. The default location is one directory level
# above the current app directory.
# This is used with CY_GETLIBS_SHARED_NAME variable, which specifies the directory name.
CY_GETLIBS_SHARED_PATH=../

# Directory name of the shared repo location.
#
CY_GETLIBS_SHARED_NAME=mtb_shared

# Absolute path to the compiler's "bin" directory.
#
# The default depends on the selected TOOLCHAIN (GCC_ARM uses the ModusToolbox
# IDE provided compiler by default).
CY_COMPILER_PATH=


# Locate ModusToolbox IDE helper tools folders in default installation
# locations for Windows, Linux, and macOS.
CY_WIN_HOME=$(subst \,/,$(USERPROFILE))
CY_TOOLS_PATHS ?= $(wildcard \
    $(CY_WIN_HOME)/ModusToolbox/tools_* \
    $(HOME)/ModusToolbox/tools_* \
    /Applications/ModusToolbox/tools_*)

# If you install ModusToolbox IDE in a custom location, add the path to its
# "tools_X.Y" folder (where X and Y are the version number of the tools
# folder). Make sure you use forward slashes.
CY_TOOLS_PATHS+=

# Default to the newest installed tools folder, or the users override (if it's
# found).
CY_TOOLS_DIR=$(lastword $(sort $(wildcard $(CY_TOOLS_PATHS))))

ifeq ($(CY_TOOLS_DIR),)
$(error Unable to find any of the available CY_TOOLS_PATHS -- $(CY_TOOLS_PATHS). On Windows, use forward slashes.)
endif

$(info Tools Directory: $(CY_TOOLS_DIR))

include $(CY_TOOLS_DIR)/make/start.mk
