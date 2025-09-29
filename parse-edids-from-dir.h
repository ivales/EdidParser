#ifndef __PARSE_EDIDS__FROM_DIR_H_
#define __PARSE_EDIDS__FROM_DIR_H_

#include <string>

std::string extract_cec(const std::string& edid_text);
std::string extract_year(const std::string& edid_text);
std::string bt2020ycc(const std::string& edid_text);
std::string hdr(const std::string& edid_text);
std::string hdmi14_getinfo(const std::string& edid_text);
std::string hdmi20_getinfo(const std::string& edid_text);
std::string other_getinfo(const std::string& edid_text);
std::string hdr_result_getinfo(const std::string& edid_text);
std::string deepcolor444_getinfo(const std::string& edid_text);
std::string deepcolor420_getinfo(const std::string& edid_text);
std::string maxmode_getinfo(const std::string& edid_text);
std::string ext_mode_getinfo(const std::string& edid_text, const std::string& hdmi20);
std::string problem_getinfo(const std::string& maxmode);
std::string type_getinfo(const std::string& maxmode,
                         const std::string& hdr,
                         const std::string& hdr_st_hlg,
                         const std::string& deepcolor444,
                         const std::string& deepcolor420,
                         const std::string& ext_mode,
                         const std::string& bt2020ycc);


#endif

