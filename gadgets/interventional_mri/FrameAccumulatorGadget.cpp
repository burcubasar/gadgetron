#include "FrameAccumulatorGadget.h"
#include "ismrmrd/meta.h"
//#include "mri_core_def.h"

#include <vector>



namespace Gadgetron{

  FrameAccumulatorGadget::FrameAccumulatorGadget(){}
  
  FrameAccumulatorGadget::~FrameAccumulatorGadget(){
     };
  
  
  
  int FrameAccumulatorGadget::process_config(ACE_Message_Block* mb) {

    ISMRMRD::IsmrmrdHeader hdr;
    ISMRMRD::deserialize(mb->rd_ptr(),hdr);

	return GADGET_OK;
   }


 
  int FrameAccumulatorGadget::process(GadgetContainerMessage<ISMRMRD::ImageHeader>* m1, GadgetContainerMessage< hoNDArray<float > >* m2) {

     if (m1->getObjectPtr()->image_type == ISMRMRD::ISMRMRD_IMTYPE_MAGNITUDE) { //only operate on magnitude images for now
       
        ISMRMRD::ImageHeader h;
        h = *(m1->getObjectPtr());

	float im;
	im = *(m2->getObjectPtr()->get_data_ptr());

	std::vector<float> buf_;

	
        buf_.push_back(im);
        header_.push_back(h);

	// need 10 frames for SVD
	 if(buf_.size() == 10)
	 {
	  GDEBUG("10 frames\n"); 
	 
	  /*
          // pop the top one
	  buf_.pop_back(buf_.begin());
            */
	  } 


     } 

     
      // send out result
       if (this->next()->putq(m1) < 0) {
                                 		GDEBUG("Failed to pass on data to next Gadget\n");
                                 		return GADGET_FAIL;
                                 	}
        m1->release();
       return GADGET_OK;
	
    }

   GADGET_FACTORY_DECLARE(FrameAccumulatorGadget)
   
}



