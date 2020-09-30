#include "argument_processor_change.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>
#include <wsjcpp_safe_scripting.h>

// ---------------------------------------------------------------------
// ArgumentProcessorChange

ArgumentProcessorChange::ArgumentProcessorChange() 
: WsjcppArgumentProcessor({"change", "ch"}, "Change some basic variables in wsjcpp.yml", "Change some basic variables in wsjcpp.yml") {
    registryProcessor(new ArgumentProcessorChangeVersion());
    registryProcessor(new ArgumentProcessorChangeVersionFile());
    
    // registryProcessor(new ArgumentProcessorGenerateCreate());
    // registryProcessor(new ArgumentProcessorGenerateDelete());
}

// ---------------------------------------------------------------------

int ArgumentProcessorChange::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------
// ArgumentProcessorChangeVersion

ArgumentProcessorChangeVersion::ArgumentProcessorChangeVersion() 
: WsjcppArgumentProcessor({"version", "ver"}, "Change version of current wsjcpp-package", "Change version of current wsjcpp-package") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorChangeVersion::exec(
    const std::vector<std::string> &vRoutes, 
    const std::vector<std::string> &vSubParams
) {

    if (vSubParams.size() == 0) {
        std::cout << "Expected parameter %version%" << std::endl;
        return -1;
    }
    std::string sVersion = vSubParams[0];

    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (!pkg.setVersion(sVersion)) {
        return -1;
    }

    pkg.save();
    pkg.updateAutogeneratedFiles();
    return 0;
}


// ---------------------------------------------------------------------
// ArgumentProcessorChangeVersionFile

ArgumentProcessorChangeVersionFile::ArgumentProcessorChangeVersionFile() 
: WsjcppArgumentProcessor({"version-file", "ver-file"}, "version-file updating 'on' or 'off'", "version-file updating 'on' or 'off'") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorChangeVersionFile::exec(
    const std::vector<std::string> &vRoutes, 
    const std::vector<std::string> &vSubParams
) {

    if (vSubParams.size() == 0) {
        std::cout << "Expected parameter 'on' or 'off'" << std::endl;
        return -1;
    }

    std::string sValue = vSubParams[0];
    if (sValue != "on" && sValue != "off") {
        std::cout << "Expected parameter 'on' or 'off' but not '" <<  sValue << "'" << std::endl;
        return -1;
    }

    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (!pkg.setAutoGeneratedFileIncludeVersionFile(sValue == "on")) {
        return -1;
    }

    pkg.save();
    pkg.updateAutogeneratedFiles();
    return 0;
}