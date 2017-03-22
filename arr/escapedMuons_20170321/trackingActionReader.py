from readGallery import GalleryReaderBase  # Necessary for the base class

class TrackingActionArtRecordReader(GalleryReaderBase):
  def __init__(self, inputTag):
    GalleryReaderBase.__init__(self, inputTag)
    self.names = ['fileEntry', 'eventEntry', 'trackType', 'trackID', 
                  'parentTrackID', 'turn', 'volumeUID', 'status',  'p', 'e', 'x', 'y', 'z', 'px', 'py', 'pz']

  def prepare(self, ROOT, ev):
    GalleryReaderBase.prepare(self, ROOT, ev)
    self.getValidHandle = ev.getValidHandle(ROOT.vector(ROOT.gm2truth.TrackingActionArtRecord))

  def fill(self, ROOT, ev):

    validHandle = self.getValidHandle(self.inputTag)  # Get the valid handle for 
                                                      # gm2truth::TrackingActionArtRecord

    if not validHandle.empty():                       # Does it have data?

      p = validHandle.product()                       # Get the corresponding data product (maybe a vector)

      # Fill from gm2truth::TrackingActionArtRecord
      for e in p:                             # Loop over elements and fill
        
        # Only accept the primary muon death and its first generation daughters birth
        if (e.trackID == 1 and e.status == 1) or (e.parentTrackID == 1 and e.status == 0):
        
          self.vals.append(
            [ ev.fileEntry(), ev.eventEntry(), e.trackType, e.trackID, 
              e.parentTrackID, e.turn, e.volumeUID, e.status, e.p, e.e, 
              e.x, e.y, e.z, e.px, e.py, e.pz ])

    return True
