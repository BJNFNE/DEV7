# Function to log debug info to console
function print_debug_info {
    param([string]$info)
    Write-Output "$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') - $info"
}

# Check for the presence of required commands or utilities
function check_command {
    param([string]$cmd, [string]$desc)
    if (Get-Command $cmd -ErrorAction SilentlyContinue) {
        print_debug_info "$desc found at $((Get-Command $cmd).Source)"
        return $true
    } else {
        print_debug_info "$desc is required but not found. - Not installed"
        return $false
    }
}

# Check for the presence of Visual Studio folder on hard drives
function check_visual_studio {
    $vs_installed = $false
    $driveLetters = "C", "D", "E"
    $vs_folder_name = "Microsoft Visual Studio"
    
    foreach ($drive in $driveLetters) {
        $vs_path = "${drive}:\Program Files (x86)\$vs_folder_name"
        if (Test-Path $vs_path) {
            $vs_installed = $true
            print_debug_info "Visual Studio found at $vs_path"
            break
        }
    }

    if (-not $vs_installed) {
        print_debug_info "Visual Studio is required but not found. - Not installed"
    }

    return $vs_installed
}

# Check for the presence of Python3 folder on hard drives
function check_python3 {
    $python3_installed = $false
    $driveLetters = "C", "D", "E"
    $python3_folder_name = "Python3"
    
    foreach ($drive in $driveLetters) {
        $python3_path = "${drive}:\Program Files (x86)\$python3_folder_name"
        if (Test-Path $python3_path) {
            $python3_installed = $true
            print_debug_info "Python3 found at $python3_path"
            break
        }
    }

    if (-not $python3_installed) {
        print_debug_info "Python3 is required but not found. - Not installed"
    }

    return $python3_installed
}

Write-Output "Checking your system..."

# Check for the presence of essential commands
$python_command_found = check_command "python" "Python 3"

# Check for the presence of Visual Studio folder
$vs_found = check_visual_studio

# Check for the presence of Python3 folder
$python3_found = check_python3

# Final output based on checks
if ($python_command_found -and $vs_found -and $python3_found) {
    Write-Output "Checking complete. You can now compile DEV7 Tools."
} else {
    Write-Output "Some requirements are missing. Please address the issues above."
}
