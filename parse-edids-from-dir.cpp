#include <cstddef>
#include <string>
#include <cstring>


std::string extract_cec(const std::string& edid_text) {
	size_t pos = edid_text.find("Source physical address:");
	if (pos != std::string::npos) {
		size_t start = pos + strlen("Source physical address:");
		if (start + 8 <= edid_text.size()) {
			return edid_text.substr(start, 8);
		}
	}
	return "";
}

std::string extract_year(const std::string& edid_text) {
    size_t pos_made_in = edid_text.find("Made in:");
    std::string year;

    if (pos_made_in != std::string::npos) {
        size_t start = pos_made_in;
        size_t end = edid_text.find('\n', start);
        if (end == std::string::npos)
            end = edid_text.length();

        std::string made_in_str = edid_text.substr(start, end - start);
        if (made_in_str.size() >= 4)
            year = made_in_str.substr(made_in_str.size() - 4);
        else
            year = "";
    }

    if (year.empty()) {
        size_t pos_model_year = edid_text.find("Model year:");
        if (pos_model_year != std::string::npos) {
            size_t start = pos_model_year;
            size_t end = edid_text.find('\n', start);
            if (end == std::string::npos)
                end = edid_text.length();

            std::string model_year_str = edid_text.substr(start, end - start);
            if (model_year_str.size() >= 4)
                year = model_year_str.substr(model_year_str.size() - 4);
            else
                year = "";
        }
    }
    return year;
}

std::string bt2020ycc(const std::string& edid_text) {
return (edid_text.find("BT2020YCC") != std::string::npos) ? "Y" : "";
}

std::string hdr(const std::string& edid_text) {
return (edid_text.find("HDR10+") != std::string::npos) ? "HDR10+" : "";
}

std::string hdmi14_getinfo(const std::string& edid_text) {
    size_t pos = edid_text.find("Maximum TMDS clock:");
    if (pos != std::string::npos) {
        size_t start_index = pos + 20;
        size_t end_index = start_index + 7;
        if (end_index <= edid_text.size()) {
            return edid_text.substr(start_index, 7);
        } else {
            return edid_text.substr(start_index);
        }
    } else {
        return "No TMDS";
    }
}

std::string hdmi20_getinfo(const std::string& edid_text) {
    size_t vic_pos = edid_text.find("VIC  96");
    if (vic_pos != std::string::npos) {
        size_t tmds_pos = edid_text.find("Maximum TMDS Character Rate:");
        if (tmds_pos != std::string::npos) {
            size_t start_index = tmds_pos + 29;
            size_t end_index = tmds_pos + 36;
            if (end_index <= edid_text.size()) {
                return edid_text.substr(start_index, 7);
            } else {
                return edid_text.substr(start_index);
            }
        } else {
            return "No TMDS";
        }
    } else {
        return "-";
    }
}

std::string other_getinfo(const std::string& edid_text) {
    std::string other;
    if (edid_text.find("BT2020RGB") != std::string::npos) {
        other += "BT2020RGB,";
    }
    if (edid_text.find("xvYCC") != std::string::npos) {
        other += "xvYCC,";
    }
    if (edid_text.find("BT2020cYCC") != std::string::npos) {
        other += "BT2020cYCC,";
    }
    if (!other.empty()) {
        other.pop_back();
    }
    return other;
}

std::string hdr_result_getinfo(const std::string& edid_text) {
    std::string result;
    if (edid_text.find("Hybrid Log-Gamma") != std::string::npos) {
        result += "HLG,";
    }
    if (edid_text.find("SMPTE ST2084") != std::string::npos) {
        result += "ST2084,";
    }
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

std::string deepcolor444_getinfo(const std::string& edid_text) {
    std::string deepcolor444;
    if (edid_text.find("DC_48bit") != std::string::npos) {
        deepcolor444 += "16,";
    }
    if (edid_text.find("DC_36bit") != std::string::npos) {
        deepcolor444 += "12,";
    }
    if (edid_text.find("DC_30bit") != std::string::npos) {
        deepcolor444 += "10,";
    }
    if (edid_text.find("DC_Y444") != std::string::npos) {
        deepcolor444 += "Y444,";
    }
    if (!deepcolor444.empty()) {
        deepcolor444.pop_back();
    }
    return deepcolor444;
}

std::string deepcolor420_getinfo(const std::string& edid_text) {
    std::string deepcolor420;
    if (edid_text.find("Supports 16-bits/component Deep Color 4:2:0 Pixel Encoding") != std::string::npos) {
        deepcolor420 += "16,";
    }
    if (edid_text.find("Supports 12-bits/component Deep Color 4:2:0 Pixel Encoding") != std::string::npos) {
        deepcolor420 += "12,";
    }
    if (edid_text.find("Supports 10-bits/component Deep Color 4:2:0 Pixel Encoding") != std::string::npos) {
        deepcolor420 += "10,";
    }
    if (!deepcolor420.empty()) {
        deepcolor420.pop_back();
    }
    return deepcolor420;
}

std::string maxmode_getinfo(const std::string& edid_text) {
    size_t vd_start = edid_text.find("Video Data Block");
    size_t ad_start = edid_text.find("Audio Data Block");
    size_t vdb_start = edid_text.find("YCbCr 4:2:0 Video Data Block");
    size_t vsadb_start = edid_text.find("Vendor-Specific Audio Data Block");
    size_t cmvdb_start = edid_text.find("YCbCr 4:2:0 Capability Map Data Block");
    size_t vsdb14_start = edid_text.find("Vendor-Specific Data Block");

    std::string edid_vdblock = (vd_start != std::string::npos && ad_start != std::string::npos && vd_start < ad_start)
        ? edid_text.substr(vd_start, ad_start - vd_start)
        : "";

    std::string edid_420vdb = (vdb_start != std::string::npos && vsadb_start != std::string::npos && vdb_start < vsadb_start)
        ? edid_text.substr(vdb_start, vsadb_start - vdb_start)
        : "";

    std::string edid_420cmvdb = (cmvdb_start != std::string::npos)
        ? edid_text.substr(cmvdb_start)
        : "";

    std::string edid_14_vsdb = (vsdb14_start != std::string::npos)
        ? edid_text.substr(vsdb14_start)
        : "";

    auto contains = [](const std::string& haystack, const std::string& needle) -> bool {
        return haystack.find(needle) != std::string::npos;
    };

    bool cond1 = contains(edid_vdblock, "VIC  198") && (contains(edid_420vdb, "VIC  198") || contains(edid_420cmvdb, "VIC  198"));
    if (cond1) {
        if (contains(edid_vdblock, "VIC  199")) {
            return "4320p50,60Hz444,420";
        } else {
            return "4320p50Hz444,420";
        }
    } else if (contains(edid_vdblock, "VIC  198")) {
        if (contains(edid_vdblock, "VIC  199")) {
            return "4320p50,60Hz444";
        } else {
            return "4320p50Hz444";
        }
    } else if (contains(edid_420vdb, "VIC  198") || contains(edid_420cmvdb, "VIC  198")) {
        if (contains(edid_420vdb, "VIC  199") || contains(edid_420cmvdb, "VIC  199")) {
            return "4320p50,60Hz420";
        } else {
            return "4320p50Hz420";
        }
    }

    bool cond2 = contains(edid_vdblock, "VIC  96") && (contains(edid_420vdb, "VIC  96") || contains(edid_420cmvdb, "VIC  96"));
    if (cond2) {
        if (contains(edid_vdblock, "VIC  97")) {
            return "2160p50,60Hz444,420";
        } else {
            return "2160p50Hz444,420";
        }
    } else if (contains(edid_vdblock, "VIC  96")) {
        if (contains(edid_vdblock, "VIC  97")) {
            return "2160p50,60Hz444";
        } else {
            return "2160p50Hz444";
        }
    } else if (contains(edid_420vdb, "VIC  96") || contains(edid_420cmvdb, "VIC  96")) {
        if (contains(edid_420vdb, "VIC  97") || contains(edid_420cmvdb, "VIC  97")) {
            return "2160p50,60Hz420";
        } else {
            return "2160p50Hz420";
        }
    }

    if (contains(edid_vdblock, "VIC  101") || contains(edid_vdblock, "VIC  102")) {
        return "4096x";
    }
    if (contains(edid_vdblock, "VIC  95")) {
        return "2160p24,25,30Hz";
    }
    if (contains(edid_14_vsdb, "3840x2160")) {
        return "2160p24,25,30HzVSDB";
    }
    if (contains(edid_14_vsdb, "4096x2160")) {
        return "4096xVSDB";
    }
    if (contains(edid_vdblock, "VIC  31")) {
        return "1080p50,60Hz";
    }
    if (contains(edid_vdblock, "VIC  34")) {
        return "1080p24,25,30Hz";
    }

    return "1080i50,60Hz";
}

std::string ext_mode_getinfo(const std::string& edid_text, const std::string& hdmi20) {
    if (hdmi20 == "-" && (edid_text.find("3840x2160") != std::string::npos || edid_text.find("4096x2160") != std::string::npos)) {
        return "VSDB 4k";
    }

    std::string ext_mode;

    if (edid_text.find("48.000000 Hz") != std::string::npos) {
        ext_mode += "48,";
    }
    if (edid_text.find("100.000000 Hz") != std::string::npos) {
        ext_mode += "100,";
    }
    if (edid_text.find("120.000000 Hz") != std::string::npos) {
        ext_mode += "120,";
    }
    if (edid_text.find("200.000000 Hz") != std::string::npos) {
        ext_mode += "200,";
    }
    if (edid_text.find("240.000000 Hz") != std::string::npos) {
        ext_mode += "240,";
    }

    if (!ext_mode.empty()) {
        ext_mode.back() = ' ';
        ext_mode += "Hz";
    }

    return ext_mode;
}

std::string problem_getinfo(const std::string& maxmode) {
    if (maxmode.find("4096xVSDB") != std::string::npos) {
        return "4096xVSDB";
    } else if (maxmode.find("4096x") != std::string::npos) {
        return "4096xVSDB";
    } else if (maxmode.find("VSDB") != std::string::npos) {
        return "3840xVSDB";
    } else {
        return "";
    }
}

std::string type_getinfo(const std::string& maxmode,
                         const std::string& hdr,
                         const std::string& hdr_st_hlg,
                         const std::string& deepcolor444,
                         const std::string& deepcolor420,
                         const std::string& ext_mode,
                         const std::string& bt2020ycc) {
    bool isHDR = (bt2020ycc == "Y") && 
                 (deepcolor444.find("10") != std::string::npos || deepcolor420.find("10") != std::string::npos) && 
                 (!hdr_st_hlg.empty());
    bool isHDR10 = isHDR && !hdr.empty();

    std::string type = "1080i";

    if (maxmode.find("2160p50,60Hz444") != std::string::npos) {
        type = "2160p";
    } else if (maxmode.find("1080p50") != std::string::npos) {
        type = "1080p";
    } else if (maxmode.find("VSDB") != std::string::npos) {
        type = "2160pVSDB";
    } else if (maxmode.find("2160p24,25,30Hz") != std::string::npos || 
               maxmode.find("2160p50,60Hz420") != std::string::npos) {
        type = "1080p";
    } else if (maxmode.find("1080p30") != std::string::npos) {
        type = "1080p30";
    }

    if (isHDR10) {
        type += "HDR10+";
    } else if (isHDR) {
        type += "HDR";
    } else if (!deepcolor444.empty()) {
        type += "DC";
    }

    if (maxmode.find("2160p50,60Hz420") != std::string::npos) {
        type += "/4k420";
    }

    return type;
}

