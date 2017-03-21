from readGallery import GalleryReaderBase  # Necessary for the base class

class RingTrackingPlaneArtRecordReader(GalleryReaderBase):
  def __init__(self, inputTag):
    GalleryReaderBase.__init__(self, inputTag)
    self.names = ['fileEntry', 'eventEntry', 'particle',
                  'trkid', 'parentid', 'pdgid', 'nturn', 'fracturn', 'detname', 
                  'detnum', 'time', 'energy', 'x', 'y', 'z', 'px', 'py', 'pz',
                  'radius', 'angle']
    # !!!! Modify the names accordingly - MUST MATCH self.vals.append CALL BELOW

  def prepare(self, ROOT, ev):
    GalleryReaderBase.prepare(self, ROOT, ev)
    self.getValidHandle = ev.getValidHandle(ROOT.vector(ROOT.gm2truth.RingTrackingPlaneArtRecord))

  def fill(self, ROOT, ev):

    validHandle = self.getValidHandle(self.inputTag)  # Get the valid handle for gm2truth::RingTrackingPlaneArtRecord

    if not validHandle.empty():                       # Does it have data?

      p = validHandle.product()                       # Get the corresponding data product (maybe a vector)

      # Fill from gm2truth::BasicArtRecord
      for e in p:                             # Loop over elements and fill
        
        f = e.basicInfo

        self.vals.append(
          [ ev.fileEntry(), ev.eventEntry(), f.particle, f.trkid, f.parentid, f.pdgid, f.nturn, e.fturn, f.detname,
            f.detnum, f.time, f.energy, f.pos.x(), f.pos.y(), f.pos.z(), 
            f.mom.x(), f.mom.y(), f.mom.z(), f.radius, f.angle ])

    return True
