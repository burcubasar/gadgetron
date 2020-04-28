#include "BufferSVDGadget.h"
#include "Context.h"
#include "Channel.h"
#include "Types.h"
#include "hoNDArray.h"
#include "hoNDKLT.h"

#include <tuple>
#include <array>

namespace {
    using namespace Gadgetron;
    using namespace Gadgetron::Core;
}

namespace Gadgetron::Core {

    BufferSVDGadget::BufferSVDGadget(
            const Context &context,
            const std::unordered_map<std::string, std::string> &props
    ) : ChannelGadget(props), context(context) {}

  void BufferSVDGadget::process(InputChannel<std::deque<Image<float>>> &in, OutputChannel &out) {
    
    for (auto buffer : in) {
      
        hoNDKLT<float> KLT;
        hoNDArray<float> PCs;
	
	using namespace Gadgetron::Indexing;		
        auto [header,tmp,meta] = buffer.front();
	int numFrames = buffer.size();
	int numElems = tmp.size();
	hoNDArray<float> data;
	/*
       	for (int x = 0; x<numFrames; x++){
	  auto [header_,data_,meta_] = buffer[x];
	  data[x*numElems] = data_;
	}
        GDEBUG("data dims: %d\n",data.size());
        out.push(Image<float> {header,data_,meta});
       */	

	/*
	for (int x = 0; x<buffer.size(); x++){
	  for (int i = 0; i<tmp.size(); i++){
       	    auto [header_,data_,meta_] = buffer[x];
            data[x*i] = data_[i];
	    }
	}
	
      	GDEBUG("data dims: %d\n",tmp.size());
        out.push(Image<float> {header,tmp,meta});
	*/
	
	/*	 
	  KLT.prepare(data, (size_t)1, (size_t)10, false);
	  KLT.transform(data,PCs,(size_t)10);
	  Image<float> image = {header,PCs,meta};
          out.push(image);
	  //  GDEBUG("data size: %d",data.size());
	  */
	  
        auto [h,dt_,mt] = buffer.front();
	out.push(Image<float> {h,dt_,mt});
	GDEBUG("buffer dims: %d\n",buffer.size());  
	
    }  
  }

    GADGETRON_GADGET_EXPORT(BufferSVDGadget);
}
