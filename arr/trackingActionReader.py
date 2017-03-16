from readGallery import GalleryReaderBase

# See https://redmine.fnal.gov/redmine/projects/gm2dataproducts/repository/entry/mc/actions/track/TrackingActionArtRecord.hh?rev=feature%2Fmdc2

class TrackingActionArtRecord(GalleryReaderBase):
  def __init__(self, inputTag):
    GalleryReaderBase.__init__(self, inputTag)
    self.names = ['fileEntry', 'eventEntry', 
                  'trackType', 'trackID', 'parentTrackID', 'turn', 'volumeUID', 'status', 'time', 't0',
                  'x', 'y', 'z', 'px', 'py', 'pz']
    
  def prepare(self, ROOT, ev):
    GalleryReaderBase.prepare(self, ROOT, ev)
    self.getValidHandle = ev.getValidHandle(ROOT.vector(ROOT.gm2truth.TrackingActionArtRecord))
        
  def fill(self, ROOT, ev):
    tr_h = self.getValidHandle(self.inputTag)
    if not tr_h.empty():
      tr = tr_h.product()
      
      for t in tr:
        self.vals.append(
          [ev.fileEntry(), ev.eventEntry(), t.trackType, t.trackID, t.parentTrackID, t.turn, t.volumeUID, 
           t.status, t.time, t.t0, t.x, t.y, t.z, t.px, t.py, t.pz]
        )
        
    return True
