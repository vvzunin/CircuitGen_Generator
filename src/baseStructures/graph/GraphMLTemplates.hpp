#pragma once

const char* mainTemplate     = R"(<?xml version="1.0" encoding="UTF-8"?>
<graphml xmlns="http://graphml.graphdrawing.org/xmlns" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xsi:schemaLocation="http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd">
  <key id="t" for="node" attr.name="type" attr.type="string"/>
%
</graphml>
)";

const char* rawGraphTemplate = R"(%  <graph id="%" edgedefault="directed">
%%  </graph>)";

const char* rawNodeTemplate  = R"(%    <node id="%">
%      <data key="t">%</data>%
%    </node>
)";

const char* rawEdgeTemplate  = R"(%    <edge source="%" target="%"/>
)";