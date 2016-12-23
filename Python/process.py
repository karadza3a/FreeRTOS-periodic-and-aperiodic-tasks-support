import re
import fileinput


class NameIndexer:
    def __init__(self):
        self.names = {}
        self.name_i = 0

    def index_for_name(self, name):
        if name not in self.names:
            self.names[name] = self.name_i
            self.name_i += 1
        return self.names[name]

    def name_for_index(self, index):
        for name, i in self.names.items():
            if index == i:
                return name


class ProcessorUsageParser:
    def __init__(self):
        self.r = re.compile("xt-(\d+)-(.+)")
        self.indexer = NameIndexer()
        self.last_id = -1
        self.started_at = -1
        self.output_text = []
        self.time_max = self.i_max = 0

    def process_line(self, l):
        groups = self.r.search(l)
        if groups:
            time, name = int(groups.group(1)), groups.group(2)
            i = self.indexer.index_for_name(name)
            if i != self.last_id:
                if self.started_at != -1:
                    last_id_name = self.indexer.name_for_index(self.last_id)
                    self.output_text.append("%10s: %d-%d" % (last_id_name, self.started_at, time))
                self.last_id = i
                self.started_at = time
                self.time_max = max(self.time_max, time)
                self.i_max = max(self.i_max, i)

    def get_result(self):
        return self.output_text, self.time_max, self.i_max


class CapacityParser:
    def __init__(self):
        self.r = re.compile("cap-(\d+)-(\d+)")
        self.output_dict = {}

    def process_line(self, l):
        groups = self.r.search(l)
        if groups:
            time, capacity = int(groups.group(1)), int(groups.group(2))
            self.output_dict[time] = capacity

    def get_result(self):
        return self.output_dict


def process(lines):
    pu_parser = ProcessorUsageParser()
    c_parser = CapacityParser()
    for l in lines:
        pu_parser.process_line(l)
        c_parser.process_line(l)

    return pu_parser, c_parser

if __name__ == '__main__':
    pu_parser, _ = process(fileinput.input())
    for line in pu_parser.output_text:
        print(line)
