#pragma once
#include <functional>
#include <stack>
#include <deque>
#include "Crypt.h"
#include "Variant.h"

class ScriptInput {
public:
	enum class OpCode : uint8_t {
		OP_FALSE = 0x00,
		OP_0 = OP_FALSE,
		OP_PUSHDATA1 = 0x4c,
		OP_PUSHDATA2 = 0x4d,
		OP_PUSHDATA4 = 0x4e,
		OP_1NEGATE = 0x4f,
		OP_RESERVED = 0x50,
		OP_TRUE = 0x51,
		OP_1 = OP_TRUE,
		OP_2 = 0x52,
		OP_3 = 0x53,
		OP_4 = 0x54,
		OP_5 = 0x55,
		OP_6 = 0x56,
		OP_7 = 0x57,
		OP_8 = 0x58,
		OP_9 = 0x59,
		OP_10 = 0x5a,
		OP_11 = 0x5b,
		OP_12 = 0x5c,
		OP_13 = 0x5d,
		OP_14 = 0x5e,
		OP_15 = 0x5f,
		OP_16 = 0x60,
		OP_NOP = 0x61,
		OP_VER = 0x62,
		OP_IF = 0x63,
		OP_NOTIF = 0x64,
		OP_VERIF = 0x65,
		OP_VERNOTIF = 0x66,
		OP_ELSE = 0x67,
		OP_ENDIF = 0x68,
		OP_VERIFY = 0x69,
		OP_RETURN = 0x6a,
		OP_TOALTSTACK = 0x6b,
		OP_FROMALTSTACK = 0x6c,
		OP_2DROP = 0x6d,
		OP_2DUP = 0x6e,
		OP_3DUP = 0x6f,
		OP_2OVER = 0x70,
		OP_2ROT = 0x71,
		OP_2SWAP = 0x72,
		OP_IFDUP = 0x73,
		OP_DEPTH = 0x74,
		OP_DROP = 0x75,
		OP_DUP = 0x76,
		OP_NIP = 0x77,
		OP_OVER = 0x78,
		OP_PICK = 0x79,
		OP_ROLL = 0x7a,
		OP_ROT = 0x7b,
		OP_SWAP = 0x7c,
		OP_TUCK = 0x7d,
		OP_CAT = 0x7e,
		OP_SUBSTR = 0x7f,
		OP_LEFT = 0x80,
		OP_RIGHT = 0x81,
		OP_SIZE = 0x82,
		OP_INVERT = 0x83,
		OP_AND = 0x84,
		OP_OR = 0x85,
		OP_XOR = 0x86,
		OP_EQUAL = 0x87,
		OP_EQUALVERIFY = 0x88,
		OP_RESERVED1 = 0x89,
		OP_RESERVED2 = 0x8a,
		OP_1ADD = 0x8b,
		OP_1SUB = 0x8c,
		OP_2MUL = 0x8d,
		OP_2DIV = 0x8e,
		OP_NEGATE = 0x8f,
		OP_ABS = 0x90,
		OP_NOT = 0x91,
		OP_0NOTEQUAL = 0x92,
		OP_ADD = 0x93,
		OP_SUB = 0x94,
		OP_MUL = 0x95,
		OP_DIV = 0x96,
		OP_MOD = 0x97,
		OP_LSHIFT = 0x98,
		OP_RSHIFT = 0x99,
		OP_BOOLAND = 0x9a,
		OP_BOOLOR = 0x9b,
		OP_NUMEQUAL = 0x9c,
		OP_NUMEQUALVERIFY = 0x9d,
		OP_NUMNOTEQUAL = 0x9e,
		OP_LESSTHAN = 0x9f,
		OP_GREATERTHAN = 0xa0,
		OP_LESSTHANOREQUAL = 0xa1,
		OP_GREATERTHANOREQUAL = 0xa2,
		OP_MIN = 0xa3,
		OP_MAX = 0xa4,
		OP_WITHIN = 0xa5,
		OP_RIPEMD160 = 0xa6,
		OP_SHA1 = 0xa7,
		OP_SHA256 = 0xa8,
		OP_HASH160 = 0xa9,
		OP_HASH256 = 0xaa,
		OP_CODESEPARATOR = 0xab,
		OP_CHECKSIG = 0xac,
		OP_CHECKSIGVERIFY = 0xad,
		OP_CHECKMULTISIG = 0xae,
		OP_CHECKMULTISIGVERIFY = 0xaf,
		OP_NOP1 = 0xb0,
		OP_CHECKLOCKTIMEVERIFY = 0xb1,
		OP_NOP2 = OP_CHECKLOCKTIMEVERIFY,
		OP_CHECKSEQUENCEVERIFY = 0xb2,
		OP_NOP3 = OP_CHECKSEQUENCEVERIFY,
		OP_NOP4 = 0xb3,
		OP_NOP5 = 0xb4,
		OP_NOP6 = 0xb5,
		OP_NOP7 = 0xb6,
		OP_NOP8 = 0xb7,
		OP_NOP9 = 0xb8,
		OP_NOP10 = 0xb9,
		OP_INVALIDOPCODE = 0xff
	};
public:
	ScriptInput(OpCode Code) :Code(Code) {
	}

	ScriptInput(const Variant& Number) :Code(OpCode::OP_0), Value(Number) {
	}

	ScriptInput(const ScriptInput& Input) :Code(Input.Code), Value(Input.Value) {

	}

	ScriptInput(ScriptInput&& Input) noexcept :Code(Input.Code), Value(std::move(Input.Value)) {

	}

	~ScriptInput() {
		// Variant handles it's own destruction.
	}

	ScriptInput& operator=(const ScriptInput& Input);

	bool operator==(const ScriptInput& Input);

	ScriptInput& operator=(ScriptInput&& Input) noexcept;

	inline Variant GetValue() const {
		return Value;
	}
	inline OpCode GetOpCode() const {
		return Code;
	}

private:
	OpCode Code;
	Variant Value;

};

class Script {

	class OpCodeNotSupportedError {

	};

	class FunctionError {

	};

	class EvaluationError {

	};


public:


	class OpCodeFunctionBase {
	public:
		virtual ~OpCodeFunctionBase() = default;
		virtual void call() = 0; // This is just a placeholder; we'll use derived class methods.
	};

	template<typename Ret, typename... Args>
	class OpCodeFunction : public OpCodeFunctionBase {
	private:
		std::function<Ret(Args...)> func;
	public:
		OpCodeFunction(std::function<Ret(Args...)> f) : func(f) {}

		Ret call(Args... args) {
			return func(args...);
		}

		void call() {

		}

	};


	Script() {
	}

	Script(std::deque<ScriptInput>& Input) {
		InitializeOpCodeFunctions();
		Inputs = Input;
	}

	Script(std::deque<ScriptInput>&& Input) {
		InitializeOpCodeFunctions();
		Inputs = std::move(Input);
	}

	Script(std::vector<uint8_t>::iterator& Input) {
		InitializeOpCodeFunctions();
		Parse(Input);
	}

	Script(const Script& Input) {
		InitializeOpCodeFunctions();
		Inputs = Input.Inputs;
	}

	Script(Script&& Input) noexcept {
		InitializeOpCodeFunctions();
		Inputs = std::move(Input.Inputs);
	}

	~Script() {
	}

	void InitializeOpCodeFunctions();

	Script& operator=(const Script& Input) {
		Inputs = Input.Inputs;
		return *this;
	}

	Script& operator=(Script&& Input) noexcept {
		Inputs = std::move(Input.Inputs);
		return *this;
	}

	void Serialize(std::vector<uint8_t>& Result, std::vector<uint8_t>::iterator& Start) const;

	void Parse(std::vector<uint8_t>::iterator& Input);

	bool Evaluate(const std::vector<uint8_t>& Hash) const;

	Script operator+(const Script& Other) const;

	void Prepend(const ScriptInput& NewScriptInput) {
		Inputs.push_front(NewScriptInput);
	}

	void Prepend(ScriptInput&& NewScriptInput) {
		Inputs.push_front(std::move(NewScriptInput));
	}
	void Append(const ScriptInput& NewScriptInput) {
		Inputs.push_back(NewScriptInput);
	}

	void Append(ScriptInput&& NewScriptInput) {
		Inputs.push_back(std::move(NewScriptInput));
	}

	void Clear() {
		Inputs.clear();
	}

private:
	std::deque<ScriptInput> Inputs;
	static std::unordered_map<ScriptInput::OpCode, std::unique_ptr<OpCodeFunctionBase>> OpCodeFunctions;
};

Script CreateScriptPubkey(const std::vector<uint8_t>& Hash160);