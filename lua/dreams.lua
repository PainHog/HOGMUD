-- dreams.lua

dreams = {
	" &cYou dream you ran Trials of the Fellowship solo.",
	" &cYou eat the most pies and win the contest.",
	" &cYou dream your god is speaking with you.",
	" &cYou flex your muscles and are impressive.",
	" &cYour quest gear just increased your stats to godly!",
	" &cYou dream your childhood was really good.",
	" &cYour gold has increased by 1,000,000!",
	" &cSturm is hunting you. He will win.",
	" &cNightmares are chasing you down.",
	" &cYou are faaaaallllling through the air.",
	" &cWake up! You're drowning with no aquabreath!",
	" &cYou are lost and your friends can't save you.",
	" &cYou stand victorious! Your name will go down in history.",
	" &cYour dead relative is visting your dreams.",
	" &cA statue is being erected in your honor.",
	" &cYou rescued the damsel in distress. She is ugly.",
	" &cYou dream you are attacked by a giant killer chihuahua!",
	" &cKallista is too busy to talk... FINALLY!!",
	" &cWelcome to Immortality!",
	" &cTaz flees from your mighty wrath!",
	" &cJoey gives you free quest equipment.",
	" &cDeath has arrived to claim your head as a trophy!",
	" &cA monkey is picking bugs out of your hair.",
	" &cJoey wants to give you free quest points!",
    " &cYou find the answer to life, the universe and everything in your pocket!",
    " &cOf course! It all makes sense now!",
    " &cSomething just happened and you missed it while sleeping!",
    " &cHey, wake up! There's someone snooping through your inventory!",
}

function random_dream( )
    return dreams[math.random(1, #dreams)] .. "&D\n\r"
end
