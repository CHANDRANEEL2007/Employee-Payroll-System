const STORAGE_KEY = "employeePayrollDemo.v1";

const sampleEmployees = [
  {
    employeeID: "EMP001",
    name: "Aarav Mehta",
    age: 29,
    gender: "Male",
    department: "Engineering",
    designation: "Software Developer",
    joiningDate: "12-06-2022",
    phone: "9876543210",
    email: "aarav.mehta@techsolutions.com",
    basicSalary: 52000,
    hra: 9000,
    da: 5200,
    bonus: 3000,
    overtimeRate: 450,
    pf: 2400,
    tax: 5200,
    insurance: 900
  },
  {
    employeeID: "EMP002",
    name: "Meera Iyer",
    age: 34,
    gender: "Female",
    department: "Finance",
    designation: "Payroll Analyst",
    joiningDate: "03-01-2021",
    phone: "9876501234",
    email: "meera.iyer@techsolutions.com",
    basicSalary: 61000,
    hra: 11000,
    da: 6100,
    bonus: 4200,
    overtimeRate: 500,
    pf: 3100,
    tax: 6500,
    insurance: 1100
  },
  {
    employeeID: "EMP003",
    name: "Kabir Singh",
    age: 27,
    gender: "Male",
    department: "HR",
    designation: "HR Executive",
    joiningDate: "18-08-2023",
    phone: "9876512345",
    email: "kabir.singh@techsolutions.com",
    basicSalary: 42000,
    hra: 7500,
    da: 4200,
    bonus: 2500,
    overtimeRate: 350,
    pf: 1900,
    tax: 3600,
    insurance: 800
  }
];

const sampleAttendance = [
  { employeeID: "EMP001", workingDays: 30, daysPresent: 28, paidLeaves: 1, unpaidLeaves: 1, overtimeHours: 6 },
  { employeeID: "EMP002", workingDays: 30, daysPresent: 30, paidLeaves: 0, unpaidLeaves: 0, overtimeHours: 3 },
  { employeeID: "EMP003", workingDays: 30, daysPresent: 26, paidLeaves: 2, unpaidLeaves: 2, overtimeHours: 1.5 }
];

const sampleLeaves = [
  { employeeID: "EMP001", paidLeave: 5, casualLeave: 2, sickLeave: 1, unpaidLeave: 1 },
  { employeeID: "EMP002", paidLeave: 7, casualLeave: 1, sickLeave: 0, unpaidLeave: 0 },
  { employeeID: "EMP003", paidLeave: 4, casualLeave: 3, sickLeave: 2, unpaidLeave: 2 }
];

function initialState() {
  return {
    employees: sampleEmployees,
    attendance: sampleAttendance,
    leaves: sampleLeaves,
    payrollText: "",
    history: [],
    lastPayslip: "",
    messages: []
  };
}

function loadState() {
  const stored = localStorage.getItem(STORAGE_KEY);
  if (!stored) return initialState();
  try {
    return { ...initialState(), ...JSON.parse(stored) };
  } catch {
    return initialState();
  }
}

function saveState(state) {
  localStorage.setItem(STORAGE_KEY, JSON.stringify(state));
}

let state = loadState();

function money(value) {
  return Number(value || 0).toLocaleString("en-IN", { maximumFractionDigits: 2 });
}

function numberValue(value) {
  const parsed = Number(value);
  return Number.isFinite(parsed) ? parsed : 0;
}

function todayText() {
  const now = new Date();
  return `${now.getDate()}-${now.getMonth() + 1}-${now.getFullYear()}`;
}

function setText(id, text) {
  const el = document.getElementById(id);
  if (el) el.textContent = text;
}

function setHTML(id, html) {
  const el = document.getElementById(id);
  if (el) el.innerHTML = html;
}

function flash(id, text, isError = false) {
  const el = document.getElementById(id);
  if (!el) return;
  el.className = `notice${isError ? " error" : ""}`;
  el.textContent = text;
}

function employeeFileText() {
  if (!state.employees.length) return "";
  return state.employees.map(e => [
    "========================================",
    `ID: ${e.employeeID}`,
    `Name: ${e.name}`,
    `Age: ${e.age}`,
    `Gender: ${e.gender}`,
    `Dept: ${e.department}`,
    `Desig: ${e.designation}`,
    `JoinDate: ${e.joiningDate}`,
    `Phone: ${e.phone}`,
    `Email: ${e.email}`,
    `Salary: ${e.basicSalary}`,
    `HRA: ${e.hra}`,
    `DA: ${e.da}`,
    `Bonus: ${e.bonus}`,
    `OTRate: ${e.overtimeRate}`,
    `PF: ${e.pf}`,
    `Tax: ${e.tax}`,
    `Insurance: ${e.insurance}`
  ].join("\n")).join("\n");
}

function attendanceFileText() {
  return state.attendance.map(r =>
    `ID: ${r.employeeID} | Work Days: ${r.workingDays} | Present: ${r.daysPresent} | Paid Leave: ${r.paidLeaves} | Unpaid Leave: ${r.unpaidLeaves} | Overtime: ${r.overtimeHours}`
  ).join("\n");
}

function leavesFileText() {
  return state.leaves.map(r =>
    `ID: ${r.employeeID} | Paid Leave: ${r.paidLeave} | Casual Leave: ${r.casualLeave} | Sick Leave: ${r.sickLeave} | Unpaid Leave: ${r.unpaidLeave}`
  ).join("\n");
}

function historyFileText() {
  return state.history.map(r => [
    "====================================================",
    `HIST_ID      : ${r.employeeID}`,
    `HIST_NAME    : ${r.employeeName}`,
    `HIST_MONTH   : ${r.payrollMonth}`,
    `HIST_NETPAY  : ${r.netSalary}`
  ].join("\n")).join("\n");
}

function fileText(name) {
  if (name === "employees") return employeeFileText();
  if (name === "attendance") return attendanceFileText();
  if (name === "leaves") return leavesFileText();
  if (name === "payroll") return state.payrollText;
  if (name === "history") return historyFileText();
  return "";
}

function renderStoragePreview(targetId = "storagePreview", active = "employees") {
  const pre = document.getElementById(targetId);
  if (!pre) return;
  pre.textContent = fileText(active) || "(file is empty)";
  document.querySelectorAll("[data-file-tab]").forEach(btn => {
    btn.classList.toggle("active", btn.dataset.fileTab === active);
  });
}

function persistAndRender() {
  saveState(state);
  renderAll();
}

function payrollTotals(employee, attendance) {
  const workingDays = attendance.workingDays > 0 ? attendance.workingDays : 1;
  const perDaySalary = employee.basicSalary / workingDays;
  const absentDays = Math.max(0, attendance.workingDays - attendance.daysPresent);
  const attendanceDeduction = absentDays * perDaySalary;
  const overtimePay = attendance.overtimeHours * employee.overtimeRate;
  const grossSalary = employee.basicSalary + employee.hra + employee.da + employee.bonus + overtimePay;
  const totalDeduction = attendanceDeduction + employee.pf + employee.tax + employee.insurance;
  const netSalary = grossSalary - totalDeduction;
  return { perDaySalary, absentDays, attendanceDeduction, overtimePay, grossSalary, totalDeduction, netSalary };
}

function generatePayslip(employee, attendance, month) {
  const totals = payrollTotals(employee, attendance);
  return [
    "",
    "====================================================",
    "              EMPLOYEE PAYROLL SLIP                 ",
    "====================================================",
    `Company Name             : TECH SOLUTIONS`,
    `Employee ID              : ${employee.employeeID}`,
    `Employee Name            : ${employee.name}`,
    `Department               : ${employee.department}`,
    `Designation              : ${employee.designation}`,
    `Payroll Month            : ${month}`,
    `Current Date             : ${todayText()}`,
    "----------------------------------------------------",
    `Basic Salary             : ${employee.basicSalary}`,
    `HRA                      : ${employee.hra}`,
    `DA                       : ${employee.da}`,
    `Bonus                    : ${employee.bonus}`,
    `Overtime Pay             : ${totals.overtimePay}`,
    `Gross Salary             : ${totals.grossSalary}`,
    "----------------------------------------------------",
    `Attendance Deduction     : ${totals.attendanceDeduction}`,
    `PF                       : ${employee.pf}`,
    `Tax                      : ${employee.tax}`,
    `Insurance                : ${employee.insurance}`,
    `Net Salary               : ${totals.netSalary}`,
    "===================================================="
  ].join("\n");
}

function employeeOptions(selected = "") {
  return state.employees.map(e =>
    `<option value="${e.employeeID}" ${e.employeeID === selected ? "selected" : ""}>${e.employeeID} - ${e.name}</option>`
  ).join("");
}

function renderDashboard() {
  setText("metricEmployees", state.employees.length);
  setText("metricDepartments", new Set(state.employees.map(e => e.department)).size);
  setText("metricAttendance", state.attendance.length);
  setText("metricPayslips", state.history.length);
  setText("recentPayslip", state.lastPayslip || "No payslip generated yet. Process payroll to fill payroll.txt and payroll_history.txt.");
  renderStoragePreview("dashboardStorage", "employees");
}

function renderEmployees() {
  const rows = state.employees.map(e => `
    <tr>
      <td>${e.employeeID}</td>
      <td>${e.name}</td>
      <td>${e.department}</td>
      <td>${e.designation}</td>
      <td>Rs. ${money(e.basicSalary)}</td>
      <td>${e.email}</td>
    </tr>
  `).join("");
  setHTML("employeeRows", rows || `<tr><td colspan="6">No employee records found.</td></tr>`);
  setHTML("updateEmployeeSelect", employeeOptions());
  setHTML("deleteEmployeeSelect", employeeOptions());
  setHTML("incrementEmployeeSelect", employeeOptions());
  renderStoragePreview("employeeStorage", "employees");
}

function renderAttendanceLeaves() {
  setHTML("attendanceEmployeeSelect", employeeOptions());
  setHTML("leaveEmployeeSelect", employeeOptions());
  const attendanceRows = state.attendance.map(r => `
    <tr>
      <td>${r.employeeID}</td>
      <td>${r.workingDays}</td>
      <td>${r.daysPresent}</td>
      <td>${r.paidLeaves}</td>
      <td>${r.unpaidLeaves}</td>
      <td>${r.overtimeHours}</td>
    </tr>
  `).join("");
  setHTML("attendanceRows", attendanceRows || `<tr><td colspan="6">No attendance records found.</td></tr>`);
  const leaveRows = state.leaves.map(r => `
    <tr>
      <td>${r.employeeID}</td>
      <td>${r.paidLeave}</td>
      <td>${r.casualLeave}</td>
      <td>${r.sickLeave}</td>
      <td>${r.unpaidLeave}</td>
    </tr>
  `).join("");
  setHTML("leaveRows", leaveRows || `<tr><td colspan="5">No leave records found.</td></tr>`);
  renderStoragePreview("attendanceStorage", "attendance");
}

function renderPayroll() {
  setHTML("payrollEmployeeSelect", employeeOptions());
  setText("payslipOutput", state.lastPayslip || "No generated payslip yet.");
  const rows = state.history.map(r => `
    <tr>
      <td>${r.employeeID}</td>
      <td>${r.employeeName}</td>
      <td>${r.payrollMonth}</td>
      <td>Rs. ${money(r.grossSalary)}</td>
      <td>Rs. ${money(r.deduction)}</td>
      <td>Rs. ${money(r.netSalary)}</td>
    </tr>
  `).join("");
  setHTML("historyRows", rows || `<tr><td colspan="6">No payroll history available.</td></tr>`);
  renderStoragePreview("payrollStorage", "payroll");
}

function renderStorage() {
  renderStoragePreview("storagePreview", document.querySelector("[data-file-tab].active")?.dataset.fileTab || "employees");
}

function renderAll() {
  renderDashboard();
  renderEmployees();
  renderAttendanceLeaves();
  renderPayroll();
  renderStorage();
}

function valuesFromForm(form) {
  return Object.fromEntries(new FormData(form).entries());
}

function employeeFromForm(form) {
  const v = valuesFromForm(form);
  return {
    employeeID: v.employeeID.trim(),
    name: v.name.trim(),
    age: numberValue(v.age),
    gender: v.gender.trim(),
    department: v.department.trim(),
    designation: v.designation.trim(),
    joiningDate: v.joiningDate.trim(),
    phone: v.phone.trim(),
    email: v.email.trim(),
    basicSalary: numberValue(v.basicSalary),
    hra: numberValue(v.hra),
    da: numberValue(v.da),
    bonus: numberValue(v.bonus),
    overtimeRate: numberValue(v.overtimeRate),
    pf: numberValue(v.pf),
    tax: numberValue(v.tax),
    insurance: numberValue(v.insurance)
  };
}

function validEmployee(employee) {
  const required = ["employeeID", "name", "gender", "department", "designation", "joiningDate", "phone", "email"];
  if (required.some(key => !employee[key])) return "Please fill all employee details.";
  if (employee.age <= 0) return "Invalid age.";
  const moneyKeys = ["basicSalary", "hra", "da", "bonus", "overtimeRate", "pf", "tax", "insurance"];
  if (moneyKeys.some(key => employee[key] < 0)) return "Salary values cannot be negative.";
  return "";
}

function attachForms() {
  document.getElementById("loginForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const v = valuesFromForm(event.currentTarget);
    if (v.username === "admin" && v.password === "admin123") {
      flash("loginMessage", "Login successful.");
    } else {
      flash("loginMessage", "Invalid username or password. Demo credentials are admin / admin123.", true);
    }
  });

  document.getElementById("exitDemo")?.addEventListener("click", () => {
    flash("loginMessage", "Thank you for using Payroll System.");
  });

  document.getElementById("addEmployeeForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const employee = employeeFromForm(event.currentTarget);
    const error = validEmployee(employee);
    if (error) return flash("employeeMessage", error, true);
    if (state.employees.some(e => e.employeeID === employee.employeeID)) {
      return flash("employeeMessage", "Error: Employee ID already exists.", true);
    }
    state.employees.push(employee);
    event.currentTarget.reset();
    flash("employeeMessage", "Employee added successfully.");
    persistAndRender();
  });

  document.getElementById("searchEmployeeForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const id = valuesFromForm(event.currentTarget).employeeID.trim();
    const employee = state.employees.find(e => e.employeeID === id);
    setHTML("searchResult", employee ? `
      <div class="notice">Employee Found: ${employee.name}, ${employee.department}, ${employee.designation}, Salary Rs. ${money(employee.basicSalary)}</div>
    ` : `<div class="notice error">Employee not found.</div>`);
  });

  document.getElementById("updateEmployeeForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const v = valuesFromForm(event.currentTarget);
    const employee = state.employees.find(e => e.employeeID === v.employeeID);
    if (!employee) return flash("employeeMessage", "Employee not found.", true);
    employee.name = v.name.trim();
    employee.department = v.department.trim();
    employee.designation = v.designation.trim();
    flash("employeeMessage", "Employee updated successfully.");
    persistAndRender();
  });

  document.getElementById("deleteEmployeeForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const id = valuesFromForm(event.currentTarget).employeeID;
    state.employees = state.employees.filter(e => e.employeeID !== id);
    state.attendance = state.attendance.filter(r => r.employeeID !== id);
    state.leaves = state.leaves.filter(r => r.employeeID !== id);
    flash("employeeMessage", "Employee deleted successfully.");
    persistAndRender();
  });

  document.getElementById("departmentSearchForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const dept = valuesFromForm(event.currentTarget).department.trim();
    const matches = state.employees.filter(e => e.department.toLowerCase() === dept.toLowerCase());
    setHTML("departmentResult", matches.length ? matches.map(e => `<div>${e.employeeID} - ${e.name}</div>`).join("") : "No employees found.");
  });

  document.getElementById("designationSearchForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const designation = valuesFromForm(event.currentTarget).designation.trim();
    const matches = state.employees.filter(e => e.designation.toLowerCase() === designation.toLowerCase());
    setHTML("designationResult", matches.length ? matches.map(e => `<div>${e.employeeID} - ${e.name}</div>`).join("") : "No employees found.");
  });

  document.getElementById("incrementForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const v = valuesFromForm(event.currentTarget);
    const employee = state.employees.find(e => e.employeeID === v.employeeID);
    const percent = numberValue(v.percent);
    if (!employee) return flash("employeeMessage", "Employee not found.", true);
    if (percent < 0) return flash("employeeMessage", "Invalid percentage.", true);
    const oldSalary = employee.basicSalary;
    employee.basicSalary += employee.basicSalary * percent / 100;
    flash("employeeMessage", `Salary updated successfully. Current Salary: ${oldSalary}. New Salary: ${employee.basicSalary}.`);
    persistAndRender();
  });

  document.getElementById("attendanceForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const v = valuesFromForm(event.currentTarget);
    const record = {
      employeeID: v.employeeID,
      workingDays: numberValue(v.workingDays),
      daysPresent: numberValue(v.daysPresent),
      paidLeaves: numberValue(v.paidLeaves),
      unpaidLeaves: numberValue(v.unpaidLeaves),
      overtimeHours: numberValue(v.overtimeHours)
    };
    if (record.workingDays <= 0) return flash("attendanceMessage", "Error: Working days must be greater than zero.", true);
    if ([record.daysPresent, record.paidLeaves, record.unpaidLeaves, record.overtimeHours].some(n => n < 0)) {
      return flash("attendanceMessage", "Error: Negative values are not allowed.", true);
    }
    if (record.daysPresent + record.paidLeaves + record.unpaidLeaves > record.workingDays) {
      return flash("attendanceMessage", "Error: Attendance exceeds total working days.", true);
    }
    const index = state.attendance.findIndex(r => r.employeeID === record.employeeID);
    if (index >= 0) state.attendance[index] = record;
    else state.attendance.push(record);
    flash("attendanceMessage", index >= 0 ? "Attendance updated successfully." : "Attendance recorded successfully.");
    persistAndRender();
  });

  document.getElementById("leaveForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const v = valuesFromForm(event.currentTarget);
    const record = {
      employeeID: v.employeeID,
      paidLeave: numberValue(v.paidLeave),
      casualLeave: numberValue(v.casualLeave),
      sickLeave: numberValue(v.sickLeave),
      unpaidLeave: numberValue(v.unpaidLeave)
    };
    if ([record.paidLeave, record.casualLeave, record.sickLeave, record.unpaidLeave].some(n => n < 0)) {
      return flash("attendanceMessage", "Error: Leave values cannot be negative.", true);
    }
    const index = state.leaves.findIndex(r => r.employeeID === record.employeeID);
    if (index >= 0) state.leaves[index] = record;
    else state.leaves.push(record);
    flash("attendanceMessage", index >= 0 ? "Leave record updated successfully." : "Leave record added successfully.");
    persistAndRender();
  });

  document.getElementById("payrollForm")?.addEventListener("submit", event => {
    event.preventDefault();
    const v = valuesFromForm(event.currentTarget);
    const employee = state.employees.find(e => e.employeeID === v.employeeID);
    const attendance = state.attendance.find(r => r.employeeID === v.employeeID);
    if (!employee) return flash("payrollMessage", "Employee not found.", true);
    if (!attendance) return flash("payrollMessage", "Attendance record not found.", true);
    const slip = generatePayslip(employee, attendance, v.month.trim());
    const totals = payrollTotals(employee, attendance);
    state.lastPayslip = slip;
    state.payrollText = `${state.payrollText}${state.payrollText ? "\n\n" : ""}${slip}\n`;
    state.history.push({
      employeeID: employee.employeeID,
      employeeName: employee.name,
      payrollMonth: v.month.trim(),
      grossSalary: totals.grossSalary,
      deduction: totals.totalDeduction,
      netSalary: totals.netSalary
    });
    flash("payrollMessage", "Payslip generated successfully.");
    persistAndRender();
  });

  document.getElementById("resetDemo")?.addEventListener("click", () => {
    state = initialState();
    persistAndRender();
  });

  document.querySelectorAll("[data-file-tab]").forEach(btn => {
    btn.addEventListener("click", () => {
      renderStoragePreview(btn.closest(".panel")?.querySelector("pre")?.id || "storagePreview", btn.dataset.fileTab);
    });
  });
}

function hydrateUpdateForm() {
  const select = document.getElementById("updateEmployeeSelect");
  if (!select) return;
  const fill = () => {
    const employee = state.employees.find(e => e.employeeID === select.value);
    if (!employee) return;
    document.getElementById("updateName").value = employee.name;
    document.getElementById("updateDepartment").value = employee.department;
    document.getElementById("updateDesignation").value = employee.designation;
  };
  select.addEventListener("change", fill);
  fill();
}

function init() {
  attachForms();
  renderAll();
  hydrateUpdateForm();
}

document.addEventListener("DOMContentLoaded", init);
