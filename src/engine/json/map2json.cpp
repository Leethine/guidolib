#include "map2json.h"
#include <sstream>
#include <iostream>
#include "json_stream.h"

// get time function...

using namespace json;

void stringToDate(std::string raw, GuidoDate &date)
{
    // get rid of the encapsulating quotation marks
    std::string str = raw;
    str.erase(str.end() - 1, str.end());
    str.erase(str.begin(), str.begin()+1);

    // first, parse the fraction
    std::stringstream ss(str);
    std::string item;
    vector<string> elems;
    while (getline(ss, item, '/')) {
        if (item != "") {
            elems.push_back(item);
        }
    }
    if (!(elems.size() == 2)) {
        date.num = 0;
        date.denom = 1;
    } else {
        date.num = atoi(elems[0].c_str());
        date.denom = atoi(elems[1].c_str());
        if (!date.denom)
            date.denom = 1;
    }
}
string dateToString(GuidoDate &date)
{
    // first, parse the fraction
    std::stringstream ss;
    ss << "\"";
    ss << date.num;
    ss << "/";
    ss << date.denom;
    ss << "\"";
    return ss.str();
}

float dateToFloat(const GuidoDate &date) {
  if ((date.num == 0) && (date.denom == 0))
    return 0.f;
  if (date.denom == 0)
    return 1000000.f;
  return (date.num * 1.f) / (date.denom * 1.f);
}


json_array * populate_json_array_with_time_map_collector(JSONFriendlyTimeMap &info)
{
    json_array * arr = new json_array();
    for (int i = 0; i < (int)(info.segments_.size()); i++) {
        json_object*  holder = new json_object();
        json_object*  score = new json_object();
        json_object*  perf = new json_object();
        score->add(new json_element("start", new json_string_value(dateToString(info.segments_[i].first.first).c_str())));
        score->add(new json_element("end", new json_string_value(dateToString(info.segments_[i].first.second).c_str())));
        perf->add(new json_element("start", new json_string_value(dateToString(info.segments_[i].second.first).c_str())));
        perf->add(new json_element("end", new json_string_value(dateToString(info.segments_[i].second.second).c_str())));
        holder->add(new json_element("score", new json_object_value(score)));
        holder->add(new json_element("perf", new json_object_value(perf)));
        arr->add(new json_object_value(holder));
    }
    return arr;
}

json_array * populate_json_array_with_time_2_graphic_map(Time2GraphicMap &info)
{
    json_array * arr = new json_array();
    for (int i = 0; i < (int)(info.size()); i++) {
        json_object*  holder = new json_object();
        json_object*  graph = new json_object();
        json_object*  mytime = new json_object();
        graph->add(new json_element("left", new json_float_value(info[i].second.left)));
        graph->add(new json_element("top", new json_float_value(info[i].second.top)));
        graph->add(new json_element("right", new json_float_value(info[i].second.right)));
        graph->add(new json_element("bottom", new json_float_value(info[i].second.bottom)));
        mytime->add(new json_element("start", new json_string_value(dateToString(info[i].first.first).c_str())));
        mytime->add(new json_element("end", new json_string_value(dateToString(info[i].first.second).c_str())));
        holder->add(new json_element("graph", new json_object_value(graph)));
        holder->add(new json_element("time", new json_object_value(mytime)));
        arr->add(new json_object_value(holder));
    }
    return arr;
}

string print_and_free_printable(json_printable *printable)
{
  ostringstream mystream;
  json_stream jstream(mystream);
  printable->print(jstream);
  delete printable;
  return mystream.str();
}


// for javascript
char * Time2GraphicMap2JSON(Time2GraphicMap &info)
{
  json_array * arr = populate_json_array_with_time_2_graphic_map(info);
  string out_str = print_and_free_printable(arr);
  char *out = (char *) malloc(strlen(out_str.c_str()) + 1);
  strcpy(out, out_str.c_str());
  return out;
}

//----------------------------------------------------------------------
char *	GuidoGetPageMap_JSON( CGRHandler gr, int pagenum, float w, float h)
{
	Time2GraphicMap outmap;
	GuidoErrCode err = GuidoGetPageMap(gr, pagenum, w, h, outmap);
	if (err != guidoNoErr) return 0;
	return Time2GraphicMap2JSON(outmap);
}

//----------------------------------------------------------------------
char *	GuidoGetStaffMap_JSON( CGRHandler gr, int pagenum, float w, float h, int staff)
{
	Time2GraphicMap outmap;
	GuidoErrCode err = GuidoGetStaffMap(gr, pagenum, w, h, staff, outmap);
	if (err != guidoNoErr) return 0;
	return Time2GraphicMap2JSON(outmap);
}

//----------------------------------------------------------------------
char *	GuidoGetVoiceMap_JSON( CGRHandler gr, int pagenum, float w, float h, int voice)
{
	Time2GraphicMap outmap;
	GuidoErrCode err = GuidoGetVoiceMap(gr, pagenum, w, h, voice, outmap);
	if (err != guidoNoErr) return 0;
	return Time2GraphicMap2JSON(outmap);
}

//----------------------------------------------------------------------
char*	GuidoGetSystemMap_JSON( CGRHandler gr, int pagenum, float w, float h)
{
	Time2GraphicMap outmap;
	GuidoErrCode err = GuidoGetSystemMap(gr, pagenum, w, h, outmap);
	if (err != guidoNoErr) return 0;
	return Time2GraphicMap2JSON(outmap);
}

//----------------------------------------------------------------------
