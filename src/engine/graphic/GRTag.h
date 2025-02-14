#ifndef GRTag_H
#define GRTag_H

/*
  GUIDO Library
  Copyright (C) 2002  Holger Hoos, Juergen Kilian, Kai Renz
  Copyright (C) 2002-2017 Grame

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#include "NVPoint.h"

class NVstring;

// The StaffManager holds different hashtables for the
// Synchronizsation elements to detect contraditions.

class GRPage;
class GRSystem;
class GRStaff;
class ARMusicalTag;

/** \brief The GRTag class is the base class for all GUIDO tags. 

	It is used to distinguish different types of tags. 
	There are Voice-Tags, Staff-Tags and System-Tags and even Page-Tags. This distinction is used to
	 build rods/springs and to find contradicting entries for tags on the different levels. 
*/

class GRTag
{
public:
	enum TAGTYPE { VOICETAG,STAFFTAG, SYSTEMTAG,PAGETAG, VOICEANDSYSTEMTAG };

					GRTag(const ARMusicalTag * artag = 0, float curLSPACE = 50.0f );
	virtual 		~GRTag();
	
	virtual bool operator!=(const GRTag &tag) const     { return !(this->operator==(tag)); }

	// this is overloaded in other classes ...
	virtual bool operator==(const GRTag &tag) const; 

            int			getIsAuto() const;
            bool		IsStateTag() const;
	virtual const NVPoint& getOffset() const    { return mTagOffset; }
	virtual float       getSize() const         { return mTagSize; }
	virtual float       getSConst() const       { return sconst; }

    // returns name of a font if present ...
	virtual const char*  getFont() const         { return fFontName.c_str(); }
	virtual const char*  getFontAttrib() const   { return fFontAttrib.c_str(); }
	virtual int          getFontSize() const     { return fFontSize; }

	virtual const unsigned char *   getColRef() const       { return mColRef; }

	virtual void        setSConst(float val)		{ sconst = val; }
            void		setTagType(TAGTYPE ntyp)	{ fTagType = ntyp; }
            TAGTYPE		getTagType() const      	{ return fTagType; }
            void		setError(int p_error)		{ fError = p_error; }
			int			getError() const			{ return fError; }

	virtual void StaffFinished(GRStaff * grstaff = 0);
	virtual void StaffBegin(GRStaff * grstaff = 0);
	virtual void RangeEnd(GRStaff * grstaff = 0);

protected:
	int 	isautotag;
	float 	sconst; // ?
	
	unsigned char * mColRef;	// for the color-parameter ... (RGBA) [0, 255]

	std::string fFontName;
	std::string fFontAttrib;
	int 		fFontSize;

	float 	mTagSize;
	NVPoint mTagOffset;

private:
	int 	fError		= 0;
	TAGTYPE fTagType	= VOICETAG;
};

#endif
