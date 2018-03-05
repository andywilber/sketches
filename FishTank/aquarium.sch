<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="8.6.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<modules>
<module name="NODEMCU" prefix="" dx="30.48" dy="20.32">
<ports>
</ports>
<variantdefs>
</variantdefs>
<parts>
</parts>
<sheets>
<sheet>
<plain>
<rectangle x1="0" y1="58.42" x2="55.88" y2="86.36" layer="91"/>
<rectangle x1="7.62" y1="5.08" x2="48.26" y2="25.4" layer="91"/>
<rectangle x1="137.16" y1="60.96" x2="160.02" y2="83.82" layer="91"/>
<rectangle x1="137.16" y1="5.08" x2="160.02" y2="27.94" layer="91"/>
<text x="20.32" y="73.66" size="1.778" layer="92">NodeMCU</text>
<text x="22.86" y="15.24" size="1.778" layer="92">OLED</text>
<text x="147.32" y="73.66" size="1.778" layer="92" rot="R180" align="center">Flow
Meter</text>
<text x="149.86" y="17.78" size="1.778" layer="92" align="center">DS18B20</text>
<text x="27.94" y="63.5" size="3.81" layer="92" align="center">3.3 G 8 7 6 5 4 3 2 1</text>
<text x="27.94" y="22.86" size="2.54" layer="92" align="center">G 3.3 D0 D1 RES DC DS</text>
<polygon width="0.1524" layer="92">
<vertex x="60.96" y="0"/>
<vertex x="60.96" y="-5.08"/>
<vertex x="63.5" y="-2.54"/>
</polygon>
<text x="60.96" y="-7.62" size="2.54" layer="92" align="center">WS2811</text>
<wire x1="-27.94" y1="88.9" x2="-12.7" y2="88.9" width="0.1524" layer="94"/>
<wire x1="-12.7" y1="88.9" x2="5.08" y2="88.9" width="0.1524" layer="94"/>
<wire x1="5.08" y1="88.9" x2="5.08" y2="86.36" width="0.1524" layer="94"/>
<wire x1="5.08" y1="88.9" x2="142.24" y2="88.9" width="0.1524" layer="94"/>
<wire x1="142.24" y1="88.9" x2="142.24" y2="83.82" width="0.1524" layer="94"/>
<wire x1="142.24" y1="88.9" x2="162.56" y2="88.9" width="0.1524" layer="94"/>
<wire x1="162.56" y1="88.9" x2="162.56" y2="38.1" width="0.1524" layer="94"/>
<wire x1="162.56" y1="38.1" x2="149.86" y2="38.1" width="0.1524" layer="94"/>
<wire x1="149.86" y1="38.1" x2="149.86" y2="27.94" width="0.1524" layer="94"/>
<wire x1="-12.7" y1="88.9" x2="-12.7" y2="0" width="0.1524" layer="94"/>
<wire x1="-12.7" y1="0" x2="58.42" y2="0" width="0.1524" layer="94"/>
<wire x1="-25.4" y1="-10.16" x2="-12.7" y2="-10.16" width="0.1524" layer="96"/>
<wire x1="-12.7" y1="-10.16" x2="76.2" y2="-10.16" width="0.1524" layer="96"/>
<wire x1="76.2" y1="-10.16" x2="149.86" y2="-10.16" width="0.1524" layer="96"/>
<wire x1="149.86" y1="-10.16" x2="149.86" y2="5.08" width="0.1524" layer="96"/>
<wire x1="-12.7" y1="-10.16" x2="-12.7" y2="-5.08" width="0.1524" layer="96"/>
<wire x1="-12.7" y1="-5.08" x2="58.42" y2="-5.08" width="0.1524" layer="96"/>
<wire x1="149.86" y1="-10.16" x2="170.18" y2="-10.16" width="0.1524" layer="96"/>
<wire x1="170.18" y1="-10.16" x2="170.18" y2="45.72" width="0.1524" layer="96"/>
<wire x1="170.18" y1="45.72" x2="149.86" y2="45.72" width="0.1524" layer="96"/>
<wire x1="149.86" y1="45.72" x2="149.86" y2="60.96" width="0.1524" layer="96"/>
<wire x1="76.2" y1="-10.16" x2="76.2" y2="73.66" width="0.1524" layer="96"/>
<wire x1="76.2" y1="73.66" x2="55.88" y2="73.66" width="0.1524" layer="96"/>
</plain>
<instances>
</instances>
<busses>
<bus name="B$1">
<segment>
<wire x1="7.62" y1="58.42" x2="7.62" y2="48.26" width="0.1524" layer="92"/>
<wire x1="7.62" y1="48.26" x2="15.24" y2="48.26" width="0.1524" layer="92"/>
<wire x1="15.24" y1="48.26" x2="15.24" y2="25.4" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$2">
<segment>
<wire x1="10.16" y1="25.4" x2="10.16" y2="53.34" width="0.1524" layer="92"/>
<wire x1="10.16" y1="53.34" x2="15.24" y2="53.34" width="0.1524" layer="92"/>
<wire x1="15.24" y1="53.34" x2="15.24" y2="58.42" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$3">
<segment>
<wire x1="20.32" y1="25.4" x2="20.32" y2="43.18" width="0.1524" layer="92"/>
<wire x1="20.32" y1="43.18" x2="22.86" y2="43.18" width="0.1524" layer="92"/>
<wire x1="22.86" y1="43.18" x2="22.86" y2="58.42" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$4">
<segment>
<wire x1="25.4" y1="25.4" x2="25.4" y2="40.64" width="0.1524" layer="92"/>
<wire x1="25.4" y1="40.64" x2="27.94" y2="40.64" width="0.1524" layer="92"/>
<wire x1="27.94" y1="40.64" x2="27.94" y2="58.42" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$5">
<segment>
<wire x1="33.02" y1="58.42" x2="33.02" y2="25.4" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$6">
<segment>
<wire x1="38.1" y1="25.4" x2="38.1" y2="33.02" width="0.1524" layer="92"/>
<wire x1="38.1" y1="33.02" x2="45.72" y2="33.02" width="0.1524" layer="92"/>
<wire x1="45.72" y1="33.02" x2="45.72" y2="58.42" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$7">
<segment>
<wire x1="45.72" y1="25.4" x2="45.72" y2="30.48" width="0.1524" layer="92"/>
<wire x1="45.72" y1="30.48" x2="40.64" y2="30.48" width="0.1524" layer="92"/>
<wire x1="40.64" y1="30.48" x2="40.64" y2="58.42" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$8">
<segment>
<wire x1="38.1" y1="58.42" x2="38.1" y2="40.64" width="0.1524" layer="92"/>
<wire x1="38.1" y1="40.64" x2="119.38" y2="40.64" width="0.1524" layer="92"/>
<wire x1="119.38" y1="40.64" x2="119.38" y2="17.78" width="0.1524" layer="92"/>
<wire x1="119.38" y1="17.78" x2="137.16" y2="17.78" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$9">
<segment>
<wire x1="137.16" y1="73.66" x2="86.36" y2="73.66" width="0.1524" layer="92"/>
<wire x1="86.36" y1="73.66" x2="86.36" y2="50.8" width="0.1524" layer="92"/>
<wire x1="86.36" y1="50.8" x2="50.8" y2="50.8" width="0.1524" layer="92"/>
<wire x1="50.8" y1="50.8" x2="50.8" y2="58.42" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$10">
<segment>
<wire x1="20.32" y1="58.42" x2="20.32" y2="45.72" width="0.1524" layer="92"/>
<wire x1="20.32" y1="45.72" x2="5.08" y2="45.72" width="0.1524" layer="92"/>
<wire x1="5.08" y1="45.72" x2="5.08" y2="-2.54" width="0.1524" layer="92"/>
<wire x1="5.08" y1="-2.54" x2="60.96" y2="-2.54" width="0.1524" layer="92"/>
</segment>
</bus>
<bus name="B$11">
<segment>
<wire x1="63.5" y1="0" x2="63.5" y2="-2.54" width="0.1524" layer="92"/>
<wire x1="63.5" y1="-2.54" x2="63.5" y2="-5.08" width="0.1524" layer="92"/>
<wire x1="63.5" y1="-2.54" x2="68.58" y2="-2.54" width="0.1524" layer="92"/>
</segment>
</bus>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</module>
</modules>
<parts>
</parts>
<sheets>
<sheet>
<plain>
<frame x1="-10.16" y1="63.5" x2="45.72" y2="88.9" columns="8" rows="5" layer="91"/>
</plain>
<instances>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
