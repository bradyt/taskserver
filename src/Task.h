////////////////////////////////////////////////////////////////////////////////
// taskd - Task Server
//
// Copyright 2006-2013, Paul Beckingham, Federico Hernandez.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_TASK
#define INCLUDED_TASK

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

class Task : public std::map <std::string, std::string>
{
public:
  static std::string defaultProject;
  static std::string defaultPriority;
  static std::string defaultDue;
  static bool searchCaseSensitive;
  static bool regex;
  static std::map <std::string, std::string> attributes;  // name -> type
  static std::map <std::string, float> coefficients;
  static float urgencyPriorityCoefficient;
  static float urgencyProjectCoefficient;
  static float urgencyActiveCoefficient;
  static float urgencyScheduledCoefficient;
  static float urgencyWaitingCoefficient;
  static float urgencyBlockedCoefficient;
  static float urgencyAnnotationsCoefficient;
  static float urgencyTagsCoefficient;
  static float urgencyNextCoefficient;
  static float urgencyDueCoefficient;
  static float urgencyBlockingCoefficient;
  static float urgencyAgeCoefficient;

public:
  Task ();                       // Default constructor
  Task (const Task&);            // Copy constructor
  Task& operator= (const Task&); // Assignment operator
  bool operator== (const Task&); // Comparison operator
  Task (const std::string&);     // Parse
  ~Task ();                      // Destructor

  void parse (const std::string&);
  std::string composeF4 () const;
#ifdef PRODUCT_TASKWARRIOR
  std::string composeJSON (bool decorate = false) const;
#endif

  // Status values.
  enum status {pending, completed, deleted, recurring, waiting};

  // Public data.
  int id;
  float urgency_value;
  bool recalc_urgency;

  bool is_blocked;
  bool is_blocking;

  int annotation_count;

  // Series of helper functions.
  static status textToStatus (const std::string&);
  static std::string statusToText (status);

  void setEntry ();
  void setEnd ();
  void setStart ();
  void setModified ();

  bool has (const std::string&) const;
  std::vector <std::string> all ();
  const std::string get (const std::string&) const;
  const std::string& get_ref (const std::string&) const;
  int get_int (const std::string&) const;
  unsigned long get_ulong (const std::string&) const;
  time_t get_date (const std::string&) const;
  void set (const std::string&, const std::string&);
  void set (const std::string&, int);                                           
  void remove (const std::string&);

#ifdef PRODUCT_TASKWARRIOR
  bool is_due () const;
  bool is_duetoday () const;
  bool is_overdue () const;
#endif

  status getStatus () const;
  void setStatus (status);

  int getTagCount () const;
  bool hasTag (const std::string&) const;
  void addTag (const std::string&);
  void addTags (const std::vector <std::string>&);
  void getTags (std::vector<std::string>&) const;
  void removeTag (const std::string&);

  bool hasAnnotations () const;
  void getAnnotations (std::map <std::string, std::string>&) const;
  void setAnnotations (const std::map <std::string, std::string>&);
  void addAnnotation (const std::string&);
  void removeAnnotations ();

#ifdef PRODUCT_TASKWARRIOR
  void addDependency (int);
  void addDependency (const std::string&);
  void removeDependency (int);
  void removeDependency (const std::string&);
  void getDependencies (std::vector <int>&) const;
  void getDependencies (std::vector <std::string>&) const;

  void getUDAs (std::vector <std::string>&) const;
  void getUDAOrphans (std::vector <std::string>&) const;

  void substitute (const std::string&, const std::string&, bool);
#endif

  void validate (bool applyDefault = true);

#ifdef PRODUCT_TASKWARRIOR
  float urgency_c () const;
  float urgency ();
#endif

private:
  int determineVersion (const std::string&);
  void parseJSON (const std::string&);
  void parseLegacy (const std::string&);
  void validate_before (const std::string&, const std::string&);

#ifdef PRODUCT_TASKWARRIOR
  inline float urgency_priority () const;
  inline float urgency_project () const;
  inline float urgency_active () const;
  inline float urgency_scheduled () const;
  inline float urgency_waiting () const;
  inline float urgency_blocked () const;
  inline float urgency_annotations () const;
  inline float urgency_tags () const;
  inline float urgency_next () const;
  inline float urgency_due () const;
  inline float urgency_blocking () const;
  inline float urgency_age () const;
#endif
};

#endif
////////////////////////////////////////////////////////////////////////////////
