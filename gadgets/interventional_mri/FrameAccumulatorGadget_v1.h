#ifndef FRAMEACCUMULATORGADGET_H_
#define FRAMEACCUMULATORGADGET_H_

#include "Gadget.h"
#include "hoNDArray.h"

#include "gadgetron_interventional_mri_export.h"

#include <ismrmrd/ismrmrd.h>



namespace Gadgetron{

  // template <typename T> class EXPORTGADGETSMRICORE FrameAccumulatorGadget:
    class EXPORTGADGETSINTERVENTIONAL_MRI FrameAccumulatorGadget :
       public Gadget2<ISMRMRD::ImageHeader, hoNDArray<float>>
       {
       public:
        GADGET_DECLARE(FrameAccumulatorGadget);

		FrameAccumulatorGadget();
	virtual ~FrameAccumulatorGadget();
	
      
    protected:
      virtual int process(GadgetContainerMessage<ISMRMRD::ImageHeader>* m1,
			  GadgetContainerMessage< hoNDArray< float > >* m2);
      virtual int process_config(ACE_Message_Block *mb);

    private:
            //std::map< int, std::vector< ACE_Message_Block* > > buffer_;
      // std::vector< hoNDArray<float> > buf_;
      //   hoNDArray<float> im;
            std::vector<ISMRMRD::ImageHeader> h;
            std::vector<ISMRMRD::ImageHeader> header_;
    };

/*

    class EXPORTGADGETSINTERVENTIONAL_MRI FrameAccumulatorGadgetUSHORT:
	   public FrameAccumulatorGadget<uint16_t>
       {
        public:
    	GADGET_DECLARE(FrameAccumulatorGadgetUSHORT);
    };

    class EXPORTGADGETSINTERVENTIONAL_MRI FrameAccumulatorGadgetFLOAT:
    	public FrameAccumulatorGadget<float>
        {
        public:
        	GADGET_DECLARE(FrameAccumulatorGadgetFLOAT);
        };
*/

}

#endif //FrameAccumulatorGadget_H
