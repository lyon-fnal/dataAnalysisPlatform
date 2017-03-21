from readGallery import GalleryReaderBase  # Necessary for the base class

class GeantStepReader(GalleryReaderBase):
  def __init__(self, inputTag, eventsToFill = []):
    GalleryReaderBase.__init__(self, inputTag)
    self.names = ['fileEntry', 'eventEntry', 'trackID', 'globalStepNum', 'totalEnergyDeposit', 
                  'stepLength', 'deltaTime', 'globalTime', 'localTime', 'volumeUID', 
                  'x', 'y', 'z', 'px', 'py', 'pz', 'sx', 'sy', 'sz']
    self.eventsToFill = eventsToFill
    print self.eventsToFill

  def prepare(self, ROOT, ev):
    GalleryReaderBase.prepare(self, ROOT, ev)
    self.getValidHandle = ev.getValidHandle(ROOT.vector(ROOT.gm2ringsim.GeantTrackRecord))

  def fill(self, ROOT, ev):

    # Do we care about this event - if not then don't bother looking?
    if self.eventsToFill and not ev.eventEntry() in self.eventsToFill:
      return True
    print 'HI'

    validHandle = self.getValidHandle(self.inputTag)  # Get the valid handle for gm2ringsim::GeantTrackRecord

    if not validHandle.empty():                       # Does it have data?

      p = validHandle.product()                       # Get the corresponding data product (maybe a vector)

      # Fill from gm2ringsim::GeantStep
      for e in p:                             # Loop over elements and fill
      
        # Get the steps
        for f in e.steps():

          self.vals.append(
            [ ev.fileEntry(), ev.eventEntry(), e.trackID(), f.globalStepNum(), 
            f.totalEnergyDeposit(), f.stepLength(), f.deltaTime(), f.globalTime(), 
            f.localTime(), f.volumeUID(), f.pos()[0], f.pos()[1], f.pos()[2], f.p()[0], 
            f.p()[1], f.p()[2], f.s()[0], f.s()[1], f.s()[2] ])


    return True
