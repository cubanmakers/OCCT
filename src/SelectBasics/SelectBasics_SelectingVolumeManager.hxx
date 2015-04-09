// Created on: 2014-08-21
// Created by: Varvara POSKONINA
// Copyright (c) 2005-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _SelectBasics_SelectingVolumeManager_HeaderFile
#define _SelectBasics_SelectingVolumeManager_HeaderFile

#include <BVH_Box.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <NCollection_Vec3.hxx>

class Bnd_Box;
class gp_Pnt;
class TColgp_Array1OfPnt;

//! This class provides an interface for selecting volume manager,
//! which is responsible for all overlap detection methods and
//! calculation of minimum depth, distance to center of geometry
//! and detected closest point on entity.
class SelectBasics_SelectingVolumeManager
{
public:

  //! Available selection types
  enum SelectionType { Point, Box, Polyline, Unknown };

public:

  SelectBasics_SelectingVolumeManager() {};

  virtual ~SelectBasics_SelectingVolumeManager() {};

  virtual const Standard_Integer GetActiveSelectionType() const = 0;

  //! Returns true if selecting volume is overlapped by box theBox
  virtual const Standard_Boolean Overlaps (const BVH_Box<Standard_Real, 3>& theBox,
                                           Standard_Real& theDepth) = 0;

  //! Returns true if selecting volume is overlapped by axis-aligned bounding box with minimum
  //! corner at point theMinPt and maximum at point theMaxPt
  virtual const Standard_Boolean Overlaps (const NCollection_Vec3<Standard_Real>& theMinPt,
                                           const NCollection_Vec3<Standard_Real>& theMaxPt) = 0;

  //! Returns true if selecting volume is overlapped by point thePt
  virtual const Standard_Boolean Overlaps (const gp_Pnt& thePt,
                                           Standard_Real& theDepth) = 0;

  //! Returns true if selecting volume is overlapped by planar convex polygon, which points
  //! are stored in theArrayOfPts, taking into account sensitivity type theSensType
  virtual const Standard_Boolean Overlaps (const Handle(TColgp_HArray1OfPnt)& theArrayOfPts,
                                           Standard_Integer theSensType,
                                           Standard_Real& theDepth) = 0;

  //! Returns true if selecting volume is overlapped by line segment with start point at thePt1
  //! and end point at thePt2
  virtual const Standard_Boolean Overlaps (const gp_Pnt& thePt1,
                                           const gp_Pnt& thePt2,
                                           Standard_Real& theDepth) = 0;

  //! Returns true if selecting volume is overlapped by triangle with vertices thePt1,
  //! thePt2 and thePt3, taking into account sensitivity type theSensType
  virtual const Standard_Boolean Overlaps (const gp_Pnt& thePt1,
                                           const gp_Pnt& thePt2,
                                           const gp_Pnt& thePt3,
                                           Standard_Integer theSensType,
                                           Standard_Real& theDepth) = 0;

  //! Calculates distance from 3d projection of user-defined selection point
  //! to the given point theCOG
  virtual const Standard_Real DistToGeometryCenter (const gp_Pnt& theCOG) = 0;

  virtual NCollection_Vec3<Standard_Real> DetectedPoint (const Standard_Real theDepth) const = 0;

protected:
  SelectionType myActiveSelectionType;      //!< Active selection type: point, box or polyline
};

#endif // _SelectBasics_SelectingVolumeManager_HeaderFile