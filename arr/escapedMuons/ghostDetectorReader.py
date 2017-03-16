from readGallery import GalleryReaderBase  # Necessary for the base class

class GhostDetectorArtRecordReader(GalleryReaderBase):
  def __init__(self, inputTag):
    GalleryReaderBase.__init__(self, inputTag)
    self.names = ['fileEntry', 'eventEntry', 'particleID', 'trackID', 'parentTrackID', 
                  'x', 'y', 'z', 
                  'px', 'py', 'pz', 
                  'sx', 'sy', 'sz', 'time', 'volumeName']

  def prepare(self, ROOT, ev):
    GalleryReaderBase.prepare(self, ROOT, ev)
    self.getValidHandle = ev.getValidHandle(ROOT.vector(ROOT.gm2truth.GhostDetectorArtRecord))

  def fill(self, ROOT, ev):

    validHandle = self.getValidHandle(self.inputTag)  # Get the valid handle for gm2truth::GhostDetectorArtRecord
    if not validHandle.empty():                       # Does it have data?
      p = validHandle.product()                       # Get the corresponding data product (maybe a vector)

      # Fill from gm2truth::GhostDetectorArtRecord
      for e in p:                             # Loop over elements and fill
        # Only look at muons, protons and neutrons
        if e.particleID in [13, -13, -2212, 2212, -2112, 2112]:
          self.vals.append(
            [ ev.fileEntry(), ev.eventEntry(), e.particleID, e.trackID, e.parentTrackID,
            e.position.x(), e.position.y(), e.position.z(), e.momentum.x(), e.momentum.y(), e.momentum.z(),
            e.spin.x(), e.spin.y(), e.spin.z(), e.time, e.volumeName ])
    return True
