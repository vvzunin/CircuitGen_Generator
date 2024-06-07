#pragma once

namespace ClassicGraphML {
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
}  // namespace ClassicGraphML

namespace OpenABCD {
const char* mainTemplate = R"(<?xml version='1.0' encoding='utf-8'?>
<graphml xmlns="http://graphml.graphdrawing.org/xmlns" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd">
  <key id="d3" for="edge" attr.name="edge_type" attr.type="long" />
  <key id="d2" for="node" attr.name="num_inverted_predecessors" attr.type="long" />
  <key id="d1" for="node" attr.name="node_type" attr.type="long" />
  <key id="d0" for="node" attr.name="node_id" attr.type="string" />
  <graph edgedefault="directed">
%  </graph>
</graphml>
)";

const char* nodeTemplate = R"(    <node id="%">
      <data key="d0">%</data>
      <data key="d1">%</data>
      <data key="d2">%</data>
    </node>
)";

const char* edgeTemplate = R"(    <edge source="%" target="%">
      <data key="d3">%</data>
    </edge>
)";
}  // namespace OpenABCD

namespace PseudoABCD {
const char* mainTemplate = R"(<?xml version='1.0' encoding='utf-8'?>
<graphml xmlns="http://graphml.graphdrawing.org/xmlns" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd">
  <key id="d1" for="node" attr.name="node_type" attr.type="long" />
  <key id="d0" for="node" attr.name="node_id" attr.type="string" />
  <graph edgedefault="directed">
%  </graph>
</graphml>
)";

const char* nodeTemplate = R"(    <node id="%">
      <data key="d0">%</data>
      <data key="d1">%</data>
    </node>
)";

const char* edgeTemplate = R"(    <edge source="%" target="%"/>
)";
}  // namespace PseudoABCD

std::map<Gates, std::string> gateToABCDType = {
    {Gates::GateAnd, "2"},
    {Gates::GateNand, "10"},
    {Gates::GateOr, "13"},
    {Gates::GateNor, "14"},
    {Gates::GateNot, "12"},
    {Gates::GateBuf, "11"},
    {Gates::GateXor, "15"},
    {Gates::GateXnor, "16"},
    {Gates::GateDefault, "ERROR"}};