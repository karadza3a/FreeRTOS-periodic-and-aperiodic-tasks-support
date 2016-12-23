#!/usr/bin/python

import fileinput
import re
from process import process

page_template = """
<html>
  <head>
  <title>Static example</title>
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>

<script type="text/javascript">
  google.charts.load("current", {packages:["timeline"]});
  google.charts.setOnLoadCallback(drawChart);
  function drawChart() {
    var container = document.getElementById('example2.2');
    var chart = new google.visualization.Timeline(container);
    var dataTable = new google.visualization.DataTable();
    dataTable.addColumn({ type: 'string', id: 'name' });
    dataTable.addColumn({ type: 'number', id: 'start' });
    dataTable.addColumn({ type: 'number', id: 'end' });
    dataTable.addRows(%s);

    var options = {
      timeline: { showRowLabels: true, groupByRowLabel: true, colorByRowLabel: true }
    };

    chart.draw(dataTable, options);
  }
</script>

  </head>
  <body>
    <h1>Processor usage timeline</h1>
        <div id="example2.2" style="height: 100%%"></div>
  </body>
</html>
"""


def main():
    pu_parser, _ = process(fileinput.input())

    data = []
    for l in pu_parser.output_text:
        r = re.compile("(.+): (\d+)-(\d+)")
        groups = r.search(l)
        name, ts, te = groups.group(1), int(groups.group(2)), int(groups.group(3))
        data.append([name, ts, te])

    print(page_template % str(data))


if __name__ == "__main__":
    main()
