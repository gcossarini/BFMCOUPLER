C $Header: /u/gcmpack/MITgcm/pkg/exf/EXF_OPTIONS.h,v 1.29 2013/10/05 19:36:12 jmc Exp $
C $Name: checkpoint64v $
C -----------------------------------------------------------------------------

C Copyright (C) 2016 Gianpiero Cossarini (gcossarini@inogs.it)

C This program is free software; you can redistribute it and/or modify it
C under the terms of the GNU General Public License as published by the Free
C Software Foundation; either version 3 of the License, or (at your option)
C any later version.
C
C This program is distributed in the hope that it will be useful,
C but WITHOUT ANY WARRANTY; without even the implied warranty of
C MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
C GNU General Public License for more details.

C -----------------------------------------------------------------------------

CBOP
C !ROUTINE: EXF_OPTIONS.h
C !INTERFACE:
C #include "EXF_OPTIONS.h"

C !DESCRIPTION:
C *==================================================================*
C | CPP options file for EXternal Forcing (EXF) package:
C | Control which optional features to compile in this package code.
C *==================================================================*
CEOP

#ifndef EXF_OPTIONS_H
#define EXF_OPTIONS_H
#include "PACKAGES_CONFIG.h"
#include "CPP_OPTIONS.h"

#ifdef ALLOW_EXF
#ifdef ECCO_CPPOPTIONS_H

C-- When multi-package option-file ECCO_CPPOPTIONS.h is used (directly included
C    in CPP_OPTIONS.h), this option file is left empty since all options that
C   are specific to this package are assumed to be set in ECCO_CPPOPTIONS.h

#else /* ndef ECCO_CPPOPTIONS_H */

C-- Package-specific Options & Macros go here

C   pkg/exf CPP options:
C   --------------------
C
C   > ( EXF_VERBOSE ) < replaced with run-time, logical parameter "exf_verbose".
C
C   >>> ALLOW_ATM_WIND <<<
C       If defined, 10-m wind fields can be read-in from files.
C
C   >>> ALLOW_ATM_TEMP <<<
C       If defined, atmospheric temperature and specific
C       humidity fields can be read-in from files.
C
C   >>> ALLOW_DOWNWARD_RADIATION <<<
C       If defined, downward long-wave and short-wave radiation
C       can be read-in form files or computed from lwflux and swflux.
C
C   >>> ALLOW_ZENITHANGLE <<<
C       If defined, ocean albedo varies with the zenith angle, and
C       incoming fluxes at the top of the atmosphere are computed
C
C   >>> ALLOW_BULKFORMULAE <<<
C       Allows the use of bulk formulae in order to estimate
C       turbulent and radiative fluxes at the ocean surface.
C
C   >>> EXF_READ_EVAP <<<
C       If defined, evaporation fields are read-in, rather than
C       computed from atmospheric state.
C
C   >>> ALLOW_RUNOFF <<<
C       If defined, river and glacier runoff can be read-in from files.
C
C   >>> ALLOW_RUNOFTEMP <<<
C       If defined, river and glacier runoff temperature
C       can be read-in from files.
C
C   >>> ATMOSPHERIC_LOADING <<<
C       If defined, atmospheric pressure can be read-in from files.
C   WARNING: this flag is set (define/undef) in CPP_OPTIONS.h
C            and cannot be changed here (in EXF_OPTIONS)
C
C   >>> EXF_SEAICE_FRACTION <<<
C       If defined, seaice fraction can be read-in from files (areaMaskFile)
C
C   >>> ALLOW_CLIMSST_RELAXATION <<<
C       Allow the relaxation to a monthly climatology of sea surface
C       temperature, e.g. the Reynolds climatology.
C
C   >>> ALLOW_CLIMSSS_RELAXATION <<<
C       Allow the relaxation to a monthly climatology of sea surface
C       salinity, e.g. the Levitus climatology.
C
C   >>> USE_EXF_INTERPOLATION <<<
C       Allows specification of arbitrary Cartesian input grids.
C
C   ====================================================================
C
C       The following CPP options:
C
C          ALLOW_ATM_WIND              (WIND)
C          ALLOW_ATM_TEMP              (TEMP)
C          ALLOW_DOWNWARD_RADIATION    (DOWN)
C          ALLOW_BULKFORMULAE          (BULK)
C          EXF_READ_EVAP               (EVAP)
C
C       permit the ocean-model forcing configurations listed in the
C       table below.  The first configuration is the default,
C       flux-forced, ocean model.  The next four are stand-alone
C       configurations that use pkg/exf, open-water bulk formulae to
C       compute the missing surface fluxes from atmospheric variables.
C       The last four configurations can be used in conjunction with
C       pkg/seaice to model ice-covered regions.  The forcing fields
C       in the rightmost column are defined in exf_fields.
C
C
C    WIND |TEMP |DOWN |BULK |EVAP |            actions
C    -----|-----|-----|-----|-----|-------------------------------------
C         |     |     |     |     |
C      -  |  -  |  -  |  -  |  -  | Read-in ustress, vstress, hflux,
C         |     |     |     |     | swflux, and sflux.
C         |     |     |     |     |
C     def | def | def | def |  -  | Read-in uwind, vwind, atemp, aqh,
C         |     |     |     |     | swdown, lwdown, precip, and runoff.
C         |     |     |     |     | Compute ustress, vstress, hflux,
C         |     |     |     |     | swflux, and sflux.
C         |     |     |     |     |
C     def | def |  -  | def |  -  | Read-in uwind, vwind, atemp, aqh,
C         |     |     |     |     | swflux, lwflux, precip, and runoff.
C         |     |     |     |     | Compute ustress, vstress, hflux,
C         |     |     |     |     | and sflux.
C         |     |     |     |     |
C     def |  -  |  -  | def |  -  | Read-in uwind, vwind, hflux,
C         |     |     |     |     | swflux, and sflux.
C         |     |     |     |     | Compute ustress and vstress.
C         |     |     |     |     |
C      -  | def |  -  | def |  -  | Read-in ustress, vstress, atemp,
C         |     |     |     |     | aqh, swflux, lwflux, precip, and
C         |     |     |     |     | runoff.  Compute hflux and sflux.
C         |     |     |     |     |
C     def | def |  -  |  -  | def | Read-in uwind, vwind, atemp, aqh,
C         |     |     |     |     | swflux, lwflux, precip, runoff,
C         |     |     |     |     | and evap.
C         |     |     |     |     |
C     def | def |  -  | def |  -  | Read-in uwind, vwind, atemp, aqh,
C         |     |     |     |     | swflux, lwflux, precip, and runoff.
C         |     |     |     |     | Compute open-water ustress, vstress,
C         |     |     |     |     | hflux, swflux, and evap.
C         |     |     |     |     |
C     def | def | def |  -  | def | Read-in uwind, vwind, atemp, aqh,
C         |     |     |     |     | swdown, lwdown, precip, runoff,
C         |     |     |     |     | and evap.
C         |     |     |     |     |
C     def | def | def | def |  -  | Read-in uwind, vwind, atemp, aqh,
C         |     |     |     |     | swdown, lwdown, precip, and runoff.
C         |     |     |     |     | Compute open-water ustress, vstress,
C         |     |     |     |     | hflux, swflux, and evap.
C
C   ====================================================================

C ----------------- SQ -----------------

C  (25/08/09)
C  Le opzioni relative ai pacchetti
C
C  calendar
C  exf
C
C  sono state tagliate da ECCO_CPPOPTIONS.h e
C  sono state incollate in EXF_OPTIONS.h

C ********************************************************************
C ***                     Calendar Package                         ***
C ********************************************************************
C 
C CPP flags controlling which code is included in the files that
C will be compiled.
C

C o Include the calendar tool.
#define ALLOW_CALENDAR

C ********************************************************************
C ***             External forcing Package                         ***
C ********************************************************************
C 
C o Include/exclude the external forcing package. To use this package,
C   you have to include the calendar tool as well. KPP can be switched
C   on or off. The implementation automatically takes care of this.
#define ALLOW_EXF

C   Relaxation to monthly climatologies.
#undef  ALLOW_CLIMTEMP_RELAXATION
#undef  ALLOW_CLIMSALT_RELAXATION

C   Relaxation to constant surface fields.
#undef  ALLOW_CONST_SST_RELAXATION
#undef  ALLOW_CONST_SSS_RELAXATION

C ----------------- SQ -----------------

C   Bulk formulae related flags.
#define  ALLOW_ATM_TEMP
#define  ALLOW_ATM_WIND
#define  ALLOW_DOWNWARD_RADIATION
#define  ALLOW_RUNOFF
#undef   ALLOW_RUNOFTEMP
#if (defined (ALLOW_ATM_TEMP) || defined (ALLOW_ATM_WIND))
# define ALLOW_BULKFORMULAE
# undef  ALLOW_BULK_LARGEYEAGER04
#endif

#undef EXF_READ_EVAP

C   Zenith Angle/Albedo related flags.
#ifdef ALLOW_DOWNWARD_RADIATION
# define ALLOW_ZENITHANGLE
#endif

C   Use ocean_emissivity*lwdown in lwFlux. This flag should be defined
C   unless to reproduce old results (obtained with inconsistent old code)
#ifdef ALLOW_DOWNWARD_RADIATION
# define EXF_LWDOWN_WITH_EMISSIVITY
#endif

C   Relaxation to monthly climatologies.
#undef ALLOW_CLIMSST_RELAXATION
#undef ALLOW_CLIMSSS_RELAXATION

C   Allows to read-in seaice fraction from files (areaMaskFile)
#undef EXF_SEAICE_FRACTION

C   Use spatial interpolation to interpolate
C   forcing files from input grid to model grid.
#define USE_EXF_INTERPOLATION
C   for interpolated vector fields, rotate towards model-grid axis
C   using old rotation formulae (instead of grid-angles)
#undef EXF_USE_OLD_VEC_ROTATION
C   for interpolation around N & S pole, use the old formulation
C   (no pole symmetry, single vector-comp interp, reset to 0 zonal-comp @ N.pole)
#undef EXF_USE_OLD_INTERP_POLE

#define EXF_INTERP_USE_DYNALLOC
#if ( defined (EXF_INTERP_USE_DYNALLOC) && defined (USING_THREADS) )
# define EXF_IREAD_USE_GLOBAL_POINTER
#endif

#endif /* ndef ECCO_CPPOPTIONS_H */
#endif /* ALLOW_EXF */
#endif /* EXF_OPTIONS_H */
