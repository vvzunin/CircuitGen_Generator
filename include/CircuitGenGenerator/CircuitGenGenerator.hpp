/**
 * @file CircuitGenGenerator.hpp
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Zunin Vladimir <vzunin@hse.ru>
 */
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <CircuitGenGenerator/export.hpp>

/**
 * @author Vladimir Zunin <vzunin@hse.ru>
 * @author Fuuulkrum7 <ilka747428@gmail.com>
 * @author Zunin Vladimir <vzunin@hse.ru>
 */
class OrientedGraph;

namespace CircuitGenGenerator {
CIRCUITGENGENERATOR_EXPORT
std::vector<std::pair<std::string, std::vector<std::shared_ptr<OrientedGraph>>>>
runGenerationFromJsonForGraph(std::string json_path);
CIRCUITGENGENERATOR_EXPORT
std::
    vector<std::pair<std::string, std::vector<std::string>>>
    /**
     * @author Fuuulkrum7 <ilka747428@gmail.com>
     * @author Zunin Vladimir <vzunin@hse.ru>
     */
    runGenerationFromJsonForPath(std::string json_path);
/** @author Fuuulkrum7 <ilka747428@gmail.com> */
CIRCUITGENGENERATOR_EXPORT void runGenerationFromJson(std::string json_path);

} // namespace CircuitGenGenerator
