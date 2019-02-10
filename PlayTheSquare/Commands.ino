// Commands.ino
// (c) Copyright 2017 MCQN Ltd.

#ifdef PRINT
#warning DEBUG BUILD, NO COMMAND OUTPUT
#endif

// Each Teensy communicates with a Raspberry Pi over serial, reporting events such as touch pad touched and
// released, and receiving commands in return
// Commands are terminated with CRLF, and are of the form:
//   <host-id>,<command>,<command-specific-data>
// The Raspberry Pi has host-id of 0, the Teensy board reports its TEENSY_ID value
// Commands:
//   IdRequest - ask for the host to return a kCommandIdResponse at some point.  
//               Not guaranteed to be the next command response, but just to force /some/ traffic in return
const int kCommandIdRequest = 0;
//   IdResponse - a simple packet identifying this host.
const int kCommandIdResponse = 1;
//   TouchDown - the respective touch panel has been touched
//               <panel-id>,<reading-values>
const int kCommandTouchDown = 2;
//   TouchRelease - the respective touch panel is no longer being touched
const int kCommandTouchRelease = 3;
//   SetPattern - set the pattern for the given bauble
//                <bauble-id>,<pattern-id>
const int kCommandSetPattern = 4;
//   BaubleTouched - the given bauble has been touched
//                   <bauble-id>
const int kCommandBaubleTouched = 5;
//   BaubleReleased - the given bauble has been released
//                    <bauble-id>
const int kCommandBaubleReleased = 6;
//   StreamTouchReadings - stream all readings from the given touch panel, not just when state changes
//                        <panel-id>
const int kCommandStreamTouchReadings = 7;
//   WitholdTouchReadings - only report readings from the given touch panel when state changes
//                          <panel-id>
const int kCommandWitholdTouchReadings = 8;
//   SetTouchThreshold - set the threshold value above which a "touch" is reported
//                       <panel-id>
const int kCommandSetTouchThreshold = 9;

const int kCommandBufferSize = 100;
char gCommandBuffer[kCommandBufferSize];
int gCommandBufferIdx = 0;

int getParameter(int aParamNumber)
{
  int pos = 0;
  String buf(gCommandBuffer);
  // Skip the parameters we don't want
  while ((aParamNumber-- > 0) && (pos >= 0))
  {
    pos = buf.indexOf(',', pos);
    if (pos != -1)
    {
      // Skip the "," to the start of the next parameter
      pos++;
    }
  }
  if (pos >= 0)
  {
    String remainder = buf.substring(pos);
    char first = remainder.charAt(0);
    if ((first >= '0') && (first <= '9'))
    {
      // There's a number, return it!
      return remainder.toInt();
    }
  }
  // If we get here there weren't enough parameters or the string was otherwise corrupted
  return -1;
}

void ProcessIncomingCommands()
{
  while (Serial.available())
  {
    gCommandBuffer[gCommandBufferIdx++] = Serial.read();
    if (gCommandBufferIdx >= kCommandBufferSize)
    {
      // We shouldn't get here, but for some reason we've overflowed
      // the command buffer.  Start again and assume we'll hit a
      // CRLF sometime soon...
      gCommandBufferIdx = 0;
    }
    if (gCommandBuffer[gCommandBufferIdx-1] == '\n')
    {
      // Terminate the string to be on the safe side
      gCommandBuffer[gCommandBufferIdx] = '\0';
      
      int cmd = getParameter(1);
      switch (cmd)
      {
      case kCommandIdRequest:
        ReportId();
        break;
      case kCommandSetPattern:
        {
          // Pull out the Bauble ID
          int bauble = getParameter(2);
          // And the pattern
          int pattern = getParameter(3);
          if ((bauble >= 0) && (bauble < kBaubleCount) && (pattern > 0) && (pattern < Bauble::eBaubleMax))
          {
            gBaubles[bauble]->setPattern(pattern);
          }
        }
        break;
      case kCommandBaubleTouched:
        {
          // Get the Bauble ID
          int bauble = getParameter(2);
          if ((bauble >= 0) && (bauble < kBaubleCount))
          {
            gBaubles[bauble]->touched(true, hueOffset);
          }
        }
        break;
      case kCommandBaubleReleased:
        {
          // Get the Bauble ID
          int bauble = getParameter(2);
          if ((bauble >= 0) && (bauble < kBaubleCount))
          {
            gBaubles[bauble]->touched(false, hueOffset);
          }
        }
        break;
      case kCommandStreamTouchReadings:
        {
          int touchPad = getParameter(2);
          if ((touchPad >= 0) && (touchPad < kTouchPadCount))
          {
            gStreamTouchPadReadings[touchPad] = true;
          }
        }
        break;
      case kCommandWitholdTouchReadings:
        {
          int touchPad = getParameter(2);
          if ((touchPad >= 0) && (touchPad < kTouchPadCount))
          {
            gStreamTouchPadReadings[touchPad] = false;
          }
        }
        break;
      case kCommandSetTouchThreshold:
        {
          // Get the panel id
          int touchPad = getParameter(2);
          // And the threshold
          int threshold = getParameter(3);
          if ((touchPad >= 0) && (touchPad < kTouchPadCount) && (threshold > 0))
          {
            gTouchPads[touchPad].setThreshold(threshold);
          }
        }
        break;
      case kCommandTouchDown:
      case kCommandTouchRelease:
      case kCommandIdResponse:
      default:
        break;
      };
      gCommandBufferIdx = 0;
    }
  }
}

void PrintCommandHeader(int aCommand)
{
  Serial.print(TEENSY_ID);
  Serial.print(",");
  Serial.print(aCommand);
}

void ReportId()
{
  PrintCommandHeader(kCommandIdResponse);
  Serial.println(); // No data to send
}

void ReportTouchDown(int aTouchPadId, TouchSensor& aTouchPad)
{
  PrintCommandHeader(kCommandTouchDown);
  Serial.print(",");
  Serial.print(aTouchPadId);
  Serial.print(",");
  Serial.print(aTouchPad.iTouchThreshold);
  Serial.print(",");
  Serial.print(aTouchPad.iLastReading);
  Serial.print(",");
  Serial.print(aTouchPad.iLongFilter);
  Serial.print(",");
  Serial.print(500);  // Numbers for "touched" vs "untouched" chosen to be in a similar range to readings so they show up easily on the serial plotter
  Serial.println();
}

void ReportTouchRelease(int aTouchPadId, TouchSensor& aTouchPad)
{
  PrintCommandHeader(kCommandTouchRelease);
  Serial.print(",");
  Serial.print(aTouchPadId);
  Serial.print(",");
  Serial.print(aTouchPad.iTouchThreshold);
  Serial.print(",");
  Serial.print(aTouchPad.iLastReading);
  Serial.print(",");
  Serial.print(aTouchPad.iLongFilter);
  Serial.print(",");
  Serial.print(100);  // Numbers for "touched" vs "untouched" chosen to be in a similar range to readings so they show up easily on the serial plotter
  Serial.println();
}

