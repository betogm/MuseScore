//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2002-2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __CHORDREST_H__
#define __CHORDREST_H__

#include "symbol.h"
#include "duration.h"

class Score;
class Measure;
class Beam;
class Tuplet;
class Segment;
class Slur;
class Articulation;
class Lyrics;
class TabDurationSymbol;
class Spanner;

//-------------------------------------------------------------------
//   @@ ChordRest
///    Virtual base class. Chords and rests can be part of a beam
//
//   @P durationType int
//   @P beamMode     BeamMode
//-------------------------------------------------------------------

class ChordRest : public DurationElement {
      Q_OBJECT
      Q_PROPERTY(int      durationType  READ durationTypeTicks WRITE setDurationType);
      Q_PROPERTY(BeamMode beamMode      READ beamMode          WRITE undoSetBeamMode);

      TDuration _durationType;
      int _staffMove;         // -1, 0, +1, used for crossbeaming

      Spanner* _spannerFor;
      Spanner* _spannerBack;
      QList<Element*> _annotations;

   protected:
      QList<Articulation*> _articulations;
      Beam* _beam;
      BeamMode _beamMode;
      bool _up;                           // actual stem direction
      bool _small;
      Space _space;                       // cached value from layout
      QList<Lyrics*> _lyricsList;
      TabDurationSymbol* _tabDur;         // stores a duration symbol in tablature staves

   public:
      ChordRest(Score*);
      ChordRest(const ChordRest&);
      ChordRest &operator=(const ChordRest&);
      ~ChordRest();
      virtual ElementType type() const = 0;
      virtual Element* drop(const DropData&);

      Segment* segment() const                   { return (Segment*)parent(); }
      virtual Measure* measure() const           { return parent() ? (Measure*)(parent()->parent()) : 0; }

      virtual void read(XmlReader&) = 0;
      void writeProperties(Xml& xml) const;
      bool readProperties(XmlReader&);
      virtual void scanElements(void* data, void (*func)(void*, Element*), bool all=true);

      void setBeamMode(BeamMode m)              { _beamMode = m;    }
      void undoSetBeamMode(BeamMode m);
      BeamMode beamMode() const                 { return _beamMode; }

      void setBeam(Beam* b);
      virtual Beam* beam() const                { return _beam; }
      int beams() const                         { return _durationType.hooks(); }
      virtual qreal upPos()   const = 0;
      virtual qreal downPos() const = 0;
      virtual qreal centerX() const = 0;

      virtual int upLine() const                { return 0;}
      virtual int downLine() const              { return 8;}
      int line(bool up) const                   { return up ? upLine() : downLine(); }
      int line() const                          { return _up ? upLine() : downLine(); }
      virtual QPointF stemPos() const           { return canvasPos(); }    // point to connect stem
      virtual qreal stemPosX() const            { return canvasPos().x(); }
      bool up() const                           { return _up;   }
      void setUp(bool val)                      { _up = val; }

      QList<Articulation*>& articulations()     { return _articulations; }
      const QList<Articulation*>& articulations() const { return _articulations; }
      Articulation* hasArticulation(const Articulation*);

      bool small() const                        { return _small; }
      void setSmall(bool val);

      virtual void setMag(qreal val);

      int staffMove() const                     { return _staffMove; }
      void setStaffMove(int val)                { _staffMove = val; }

      Spanner* spannerFor() const               { return _spannerFor;         }
      Spanner* spannerBack() const              { return _spannerBack;        }

      void addSlurFor(Slur* s)                  { addSpannerFor((Spanner*)s);  }
      void addSlurBack(Slur* s)                 { addSpannerBack((Spanner*)s);    }
      bool removeSlurFor(Slur* s)               { return removeSpannerFor((Spanner*)s);  }
      bool removeSlurBack(Slur* s)              { return removeSpannerBack((Spanner*)s); }

      void addSpannerFor(Spanner*);
      void addSpannerBack(Spanner*);
      bool removeSpannerFor(Spanner*);
      bool removeSpannerBack(Spanner*);

      const QList<Element*>& annotations() const { return _annotations;        }
      QList<Element*>& annotations()             { return _annotations;        }
      void removeAnnotation(Element* e)          { _annotations.removeOne(e);  }

      void layoutArticulations();

      const TDuration& durationType() const      { return _durationType;        }
      void setDurationType(TDuration::DurationType t);
      void setDurationType(const QString& s);
      void setDurationType(int ticks);
      void setDurationType(const TDuration& v);
      void setDots(int n)                       { _durationType.setDots(n); }
      int dots() const                          { return _durationType.dots(); }
      int durationTypeTicks()                   { return _durationType.ticks(); }

      virtual void setTrack(int val);
      virtual int tick() const;
      virtual Space space() const               { return _space; }

      const QList<Lyrics*>& lyricsList() const { return _lyricsList; }
      QList<Lyrics*>& lyricsList()             { return _lyricsList; }
      Lyrics* lyrics(int no)                   { return _lyricsList.value(no); }
      virtual void add(Element*);
      virtual void remove(Element*);
      void removeDeleteBeam();

      virtual QVariant getProperty(P_ID propertyId) const;
      virtual bool setProperty(P_ID propertyId, const QVariant&);
      virtual QVariant propertyDefault(P_ID) const;
      };

#endif

