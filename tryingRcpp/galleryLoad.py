import ROOT

def read_header(h):
  """Make the ROOT C++ jit compiler read the specified header."""
  ROOT.gROOT.ProcessLine('#include "%s"' % h)

def provide_get_valid_handle(klass):
  """Make the ROOT C++ jit compiler instantiate the
     Event::getValidHandle member template for template
     parameter klass."""
  ROOT.gROOT.ProcessLine('template gallery::ValidHandle<%(name)s> gallery::Event::getValidHandle<%(name)s>(art::InputTag const&) const;' % {'name' : klass})

