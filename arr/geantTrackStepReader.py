from readGallery import GalleryReaderBase

# Geant track and step
# See https://redmine.fnal.gov/redmine/projects/gm2ringsim/repository/entry/debugging/GeantTrackRecord.hh?rev=feature%2Fmdc2

class GeantTrackStepRecord(GalleryReaderBase):
  def __init__(self, inputTag):
    GalleryReaderBase.__init__(self, inputTag)
    self.names = ['fileEntry', 'eventEntry', 'trackID', 'globalStepNum', 'eDep', 'l', 'deltaT', 'globalTime',
                  'localTime', 'volumeUID', 'x', 'y', 'z', 'px', 'py', 'pz']
  
  def prepare(self, ROOT, ev):
    GalleryReaderBase.prepare(self, ROOT, ev)
    self.getValidHandle = ev.getValidHandle(ROOT.vector(ROOT.gm2ringsim.GeantTrackRecord))
    
  def fill(self, ROOT, ev):
    gt_h = self.getValidHandle(self.inputTag)
    if not gt_h.empty():
      gt = gt_h.product()
      
      for t in gt:
        trackID = t.trackID()

        for s in t.steps():
          self.vals.append(
            [ev.fileEntry(), ev.eventEntry(), trackID, s.globalStepNum(), s.totalEnergyDeposit(),
             s.stepLength(), s.deltaTime(), s.globalTime(), s.localTime(), s.volumeUID(),
             s.pos()[0], s.pos()[1], s.pos()[2],
             s.p()[0], s.p()[1], s.p()[2] ]
          )
    return True
    
