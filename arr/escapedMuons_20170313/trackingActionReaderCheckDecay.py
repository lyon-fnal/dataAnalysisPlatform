# Store the muon at death and whatever it decayed to at birth

from readGallery import GalleryReaderBase  # Necessary for the base class

class TrackingActionWithDecayReader(GalleryReaderBase):
  def __init__(self, inputTag, evLimit):
    GalleryReaderBase.__init__(self, inputTag)
    self.names = ['fileEntry', 'eventEntry', 'trackType', 'trackID', 
                  'parentTrackID', 'volumeUID', 'status', 'x', 'y', 'z', 'px', 'py', 'pz', 'e', 'turn']
    self.evLimit = evLimit

  def prepare(self, ROOT, ev):
    GalleryReaderBase.prepare(self, ROOT, ev)
    self.getValidHandle = ev.getValidHandle(ROOT.vector(ROOT.gm2truth.TrackingActionArtRecord))

  def fill(self, ROOT, ev):
    
    if ev.eventEntry() > self.evLimit:
      return False
    
    validHandle = self.getValidHandle(self.inputTag)  # Get the valid handle for gm2truth::TrackingActionArtRecord

    if not validHandle.empty():                       # Does it have data?

      p = validHandle.product()                       # Get the corresponding data product (maybe a vector)

      # Fill from gm2truth::TrackingActionArtRecord
      for e in p:                             # Loop over elements and fill
      
        # Let's only accept the muon at death or whatever the muon decays to at birth
        if (e.trackID == 1) or (e.parentTrackID == 1 and e.status == 0):

          self.vals.append(
            [ ev.fileEntry(), ev.eventEntry(), e.trackType, e.trackID, e.parentTrackID,  e.volumeUID, 
              e.status, e.x, e.y, e.z, e.px, e.py, e.pz, e.e, e.turn ])

    return True
