import re
import fileinput


def process(lines):
    r = re.compile("    xt (\d+)  (\d+)")
    r_idle = re.compile("    xt (\d+)  IDLE")

    last_id = -1
    started_at = -1
    output_text = []
    time_max = i_max = 0
    for l in lines:
        groups = r_idle.search(l)
        if groups:
            time, i = int(groups.group(1)), 0
        else:
            groups = r.search(l)
            if groups:
                time, i = int(groups.group(1)), int(groups.group(2))
        if groups:
            if i != last_id:
                if started_at != -1:
                    output_text.append("%d: %d-%d" % (last_id, started_at, time))
                last_id = i
                started_at = time
                time_max = max(time_max, time)
                i_max = max(i_max, i)
    return output_text, time_max, i_max


if __name__ == '__main__':
    output, _, _ = process(fileinput.input())
    for line in output:
        print(line)
