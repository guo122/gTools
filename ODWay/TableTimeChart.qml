//====================================================================
//  TableTimeChart.qml
//  created 6.8.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQuick.Layouts 1.1
import "./ODBox" as ODBox

Rectangle {
    id: chart

    property string baseChart: "week"
    property string activeChart: "week"
    property int gridSize: 4
    property int lastDay: 7
    property real gridStep: gridSize ? (canvas.width - canvas.tickMargin) / gridSize : canvas.xGridStep

    function update() {
        if (chart.activeChart === "month") {
            gridSize = 4;
            lastDay = 30;
        } else if (chart.activeChart === "more") {
            if (chart.baseChart == "month")
            {
                lastDay += 7
            }
            else
            {
                lastDay += 1
                if (lastDay > 13)
                {
                    gridSize = 13
                }
            }
        } else if (chart.activeChart === "less") {
            if (chart.baseChart == "month")
            {
                lastDay -= 7
                if (lastDay <= 30)
                {
                    lastDay = 30
                }
            }
            else
            {
                lastDay -= 1
                if (lastDay <= 7)
                {
                    lastDay = 7
                }
                gridSize = lastDay - 1
                if (lastDay > 13)
                {
                    gridSize = 13
                }
            }
        } else {
            gridSize = 0;
            lastDay = 7;
        }

        canvas.requestPaint();
    }

    GridLayout {
        anchors.fill: parent
        columns: 6
        rows: 3
        columnSpacing: 4
        anchors.topMargin: 70
        ODBox.Button {
            id: lessButton
            text: "-"
            buttonEnabled: chart.activeChart === "less"
            onClicked: {
                chart.activeChart = "less";
                chart.update();
            }
        }

        ODBox.Button {
            id: weekButton
            text: "Week"
            buttonEnabled: chart.activeChart === "week"
            onClicked: {
                chart.activeChart = "week";
                chart.baseChart = "week";
                chart.update();
            }
        }

        ODBox.Button {
            id: monthButton
            text: "Month"
            buttonEnabled: chart.activeChart === "month"
            onClicked: {
                chart.activeChart = "month";
                chart.baseChart = "month";
                chart.update();
            }
        }

        ODBox.Button {
            id: moreButton
            text: "+"
            buttonEnabled: chart.activeChart === "more"
            onClicked: {
                chart.activeChart = "more";
                chart.update();
            }
        }

        Canvas {
            id: canvas
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 6

            property int pixelSkip: 1
            property int numPoints: 1
            property int tickMargin: 34

            property real xGridStep: (canvas.width - tickMargin) / numPoints
            property real yGridOffset: canvas.height / 26
            property real yGridStep: canvas.height / 12

            function drawBackground(ctx) {
                ctx.save();
                ctx.fillStyle = "#ffffff";
                ctx.fillRect(0, 0, canvas.width, canvas.height);
                ctx.strokeStyle = "#d7d7d7";
                ctx.beginPath();
                // Horizontal grid lines
                for (var i = 0; i < 12; i++) {
                    ctx.moveTo(0, canvas.yGridOffset + i * canvas.yGridStep);
                    ctx.lineTo(canvas.width, canvas.yGridOffset + i * canvas.yGridStep);
                }

                // Vertical grid lines
                var height = 35 * canvas.height / 36;
                var yOffset = canvas.height - height;
                var xOffset = 0;
                for (i = 0; i < chart.gridSize; i++) {
                    ctx.moveTo(xOffset + i * chart.gridStep, yOffset);
                    ctx.lineTo(xOffset + i * chart.gridStep, height);
                }
                ctx.stroke();

                // Right ticks
                ctx.strokeStyle = "#666666";
                ctx.beginPath();
                var xStart = canvas.width - tickMargin;
                ctx.moveTo(xStart, 0);
                ctx.lineTo(xStart, canvas.height);
                for (i = 0; i < 12; i++) {
                    ctx.moveTo(xStart, canvas.yGridOffset + i * canvas.yGridStep);
                    ctx.lineTo(canvas.width, canvas.yGridOffset + i * canvas.yGridStep);
                }
                ctx.moveTo(0, canvas.yGridOffset + 9 * canvas.yGridStep);
                ctx.lineTo(canvas.width, canvas.yGridOffset + 9 * canvas.yGridStep);
                ctx.closePath();
                ctx.stroke();

                ctx.restore();
            }

            function drawScales(ctx, high, low)
            {
                ctx.save();
                ctx.strokeStyle = "#888888";
                ctx.font = "10px Open Sans"

                ctx.beginPath();

                // prices on y-axis
                var x = canvas.width - tickMargin + 3;
                var priceStep = (high - low) / 9.0;
                for (var i = 0; i < 10; i += 2) {
                    var price = parseFloat(high - i * priceStep).toFixed(1);
                    ctx.text(price, x, canvas.yGridOffset + i * yGridStep - 2);
                }

                ctx.closePath();
                ctx.stroke();
                ctx.restore();
            }

            function drawVolume(ctx, points, highest)
            {
                ctx.save();
                ctx.fillStyle = "#14aaff";
                ctx.globalAlpha = 0.8;
                ctx.lineWidth = 0;
                ctx.beginPath();

                var end = points.length;
                var margin = 0;

                if (chart.activeChart === "month" || chart.activeChart === "week") {
                    margin = 8;
                    ctx.shadowOffsetX = 4;
                    ctx.shadowBlur = 3.5;
                    ctx.shadowColor = Qt.darker("#14aaff");
                }

                // To match the volume graph with price grid, skip drawing the initial
                // volume of the first day on chart.
                for (var i = 1; i < end; i += pixelSkip) {
                    var x = points[i - 1]["x"];
                    var y = points[i]["value"];
                    y = canvas.height * (y / highest);
                    y = 3 * y / 12;
                    ctx.fillRect(x, canvas.height - y + yGridOffset,
                                 canvas.xGridStep - margin, y);
                }

                ctx.stroke();
                ctx.restore();
            }

            function drawPrice(ctx, points, highest, lowest)
            {
                ctx.save();
                ctx.globalAlpha = 0.7;
                ctx.strokeStyle = "blue";

                ctx.lineWidth = 3

                ctx.beginPath();

                var end = points.length;

                var range = highest - lowest;
                if (range == 0) {
                    range = 1;
                }

                for (var i = 0; i < end; i += pixelSkip) {
                    var x = points[i]["x"];
                    var y = points[i]["value"];
                    var h = 9 * yGridStep;

                    y = h * (lowest - y)/range + h + yGridOffset;

                    if (i == 0) {
                        ctx.moveTo(x, y);
                    } else {
                        ctx.lineTo(x, y);
                    }
                }
                ctx.stroke();
                ctx.restore();
            }

            onPaint: {
                // todo
                numPoints = lastDay - 1;
                if (chart.gridSize == 0)
                    chart.gridSize = numPoints

                var ctx = canvas.getContext("2d");
                ctx.globalCompositeOperation = "source-over";
                ctx.lineWidth = 1;

                drawBackground(ctx);

                var points = [];
                var dataList = odvTimeList.getLastCKKSum(lastDay)
                var lowestValue = 0
                var highestValue = 0
                for (var i = lastDay, j = 0; i >= 0 ; i -= pixelSkip, j += pixelSkip) {
                    if (highestValue < dataList[j])
                    {
                        highestValue = dataList[j]
                    }
                    if (lowestValue > dataList[j])
                    {
                        lowestValue = dataList[j]
                    }

                    points.push({
                                    x: j * xGridStep,
                                    value: dataList[j]
                                });
                }

                drawPrice(ctx, points, highestValue, lowestValue);
                drawVolume(ctx, points, highestValue);
                drawScales(ctx, highestValue, lowestValue);

                fromDate.text = "| " + odvTimeList.getStartDate()
                toDate.text = odvTimeList.getEndDate() + " |"
            }
        }

        Text {
            id: fromDate
            color: "#000000"
            font.family: "Open Sans"
            font.pointSize: 8
            Layout.alignment: Qt.AlignLeft
        }
        Text {
            id: toDate
            color: "#000000"
            font.family: "Open Sans"
            font.pointSize: 8
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: canvas.tickMargin
            Layout.columnSpan: 5
        }
    }
}
