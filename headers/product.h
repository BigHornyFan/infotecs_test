#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <memory>

// levels of importance
enum importance { imp_lvl_1 = 1, imp_lvl_2, imp_lvl_3 , imp_min = 1, imp_max = 3};

// interface to manage with log-writer
class  writer_interface {
	
public:
        // initialising writer with log-file-name and default-importance
	virtual void init_writer(std::string, int min) = 0;
        // changes default importance 
	virtual void change_default_importance (int) = 0;
	// msg sent by default importance
	virtual void msg_default (std::string) = 0;
	// msg sent by user importance
	virtual void msg(std::string, int) = 0;
  
};

//craeat, initialise and return smart pointer with created log-writer 
extern "C" std::shared_ptr<writer_interface> create_writer(std::string filename, int num2);


#endif  // PRODUCT_H
