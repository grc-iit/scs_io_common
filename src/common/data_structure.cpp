//
// Created by neeraj on 9/16/20.
//

#include <common/data_structure.h>

std::ostream &operator<<(std::ostream &os, Data &data){
    return os << "{id_:" << data.id_ << ","
              << "data_size_:" << data.data_size_ << ","
              << "position_:" << data.position_ << ","
              << "storage_index_:" << data.storage_index_ << "}";
}

//std::ostream &operator<<(std::ostream &os, Metadata &m){
//    os << "{storage_index_:" << m.storage_index_ << ","
//       << "is_link_:" << m.is_link_ << ","
//       << "links_:{";
//    int i = 0;
//    for (auto link:m.links_) {
//        os << "{ first:" << link.first << ", "
//           << "second:" << link.first << "}";
//        if (i < m.links_.size() - 1) {
//            os << ",";
//        }
//        os << "}";
//    }
//    return os;
//}
//
//std::ostream &operator<<(std::ostream &os, DataDistribution &m){
//    return os << "{source_data_:" << m.source_data_ << ","
//              << "destination_data_:" << m.destination_data_ << ","
//              << "storage_index_:" << m.storage_index_ << "}";
//}