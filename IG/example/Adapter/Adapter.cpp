#include <iostream>

class Hindu {  // Abstract Target
        public:
	        virtual ~Hindu() = default;
	        virtual void performsHinduRitual() const = 0;
};

class HinduFemale : public Hindu {  // Concrete Target
        public:
	        virtual void performsHinduRitual() const override {std::cout << "Hindu girl performs Hindu ritual." << std::endl;}
};

class Muslim {  // Abstract Adaptee
        public:
	        virtual ~Muslim() = default;
	        virtual void performsMuslimRitual() const = 0;
};

class MuslimFemale : public Muslim {  // Concrete Adaptee
        public:
	        virtual void performsMuslimRitual() const override {std::cout << "Muslim girl performs Muslim ritual." << std::endl;}
};

class HinduRitual {
        public:
	        void carryOutRitual (Hindu* hindu) {
		        std::cout << "On with the Hindu rituals!" << std::endl;
		        hindu->performsHinduRitual();
	        }
};

class HinduAdapter : public Hindu {  // Adapter
	private:
		Muslim* muslim;
	public:
		HinduAdapter (Muslim* m) : muslim(m) {}
		virtual void performsHinduRitual() const override {muslim->performsMuslimRitual();}
};

int main() {  // Client code
	HinduFemale* hinduGirl = new HinduFemale;
	MuslimFemale* muslimGirl = new MuslimFemale;
	HinduRitual hinduRitual;
//	hinduRitual.carryOutRitual (muslimGirl);  // Will not compile of course since the parameter must be of type Hindu*.
	HinduAdapter* adaptedMuslim = new HinduAdapter (muslimGirl);  // muslimGirl has adapted to become a Hindu!
	
	hinduRitual.carryOutRitual (hinduGirl);
	hinduRitual.carryOutRitual (adaptedMuslim);  // So now muslimGirl, in the form of adaptedMuslim, participates in the hinduRitual!
                // Note that muslimGirl is carrying out her own type of ritual in hinduRitual though.
	
	delete adaptedMuslim;  // adaptedMuslim is not needed anymore
	delete muslimGirl; // muslimGirl is not needed anymore
        delete hinduGirl; // hinduGirl is not needed anymore, too
	return 0;
}