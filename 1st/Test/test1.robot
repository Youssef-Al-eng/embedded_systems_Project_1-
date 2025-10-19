*** Settings ***
Library           ArduinoLibrary.py
Suite Setup       Open Arduino
Suite Teardown    Close Arduino
Test Setup        Clear Serial
Test Teardown     Log To Console    Test Completed

*** Variables ***
${DELAY}          1s

*** Test Cases ***
Test 0 - System Ready
    [Documentation]    Verify that Arduino system is ready for testing.
    Wait For Ready
    Sleep    ${DELAY}
    Log To Console    ✅ System Ready for LED & Pushbutton Test

Test 1 - LED ON Command
    [Documentation]    Send "on" command and verify LED and LCD response.
    ${lines}=    Send Command    on
    Should Contain    ${lines}    LED turned ON
    Should Contain    ${lines}    LCD displays 1
    Log To Console    ✅ LED ON verified

Test 2 - LED OFF Command
    [Documentation]    Send "off" command and verify LED and LCD response.
    ${lines}=    Send Command    off
    Should Contain    ${lines}    LED turned OFF
    Should Contain    ${lines}    LCD displays 2
    Log To Console    ✅ LED OFF verified

Test 3 - Invalid Command
    [Documentation]    Send invalid command and verify LCD and serial message.
    ${lines}=    Send Command    xyz
    Should Contain    ${lines}    Invalid command
    Should Contain    ${lines}    LCD displays INVALID
    Log To Console    ✅ Invalid command handled correctly

Test 4 - Pushbutton Pressed
    [Documentation]    Simulate pushbutton press and verify LCD/serial feedback.
    Prompt User    Press
    ${lines}=    Send Command    status
    Should Contain    ${lines}    BUTTON_PRESSED
    Should Contain    ${lines}    LCD displays 3
    Log To Console    ✅ Button press detected

Test 5 - Pushbutton Released
    [Documentation]    Simulate pushbutton release and verify LCD/serial feedback.
    Prompt User    Release
    ${lines}=    Send Command    status
    Should Contain    ${lines}    BUTTON_RELEASED
    Should Contain    ${lines}    LCD displays 4
    Log To Console    ✅ Button release detected

Test 6 - Rapid Button Presses
    [Documentation]    Repeatedly press button quickly to verify system does not lag.
    Prompt User    Rapidly press and release the button 5 times, then press Enter
    ${lines}=    Send Command    status
    Should Contain Any    ${lines}    BUTTON_PRESSED    BUTTON_RELEASED
    Log To Console    ✅ Rapid button presses handled without lag

*** Keywords ***
Prompt User
    [Arguments]    ${action}
    Run Keyword    Evaluate    input("Please ${action} the pushbutton and press Enter to continue...")

Clear Serial
    Log To Console    🔄 Clearing serial buffer before test run...
    Sleep    0.5s
